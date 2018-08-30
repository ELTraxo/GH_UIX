#include "stdafx.h"
#include "UIX.h"


UIXPtr UIX::pUIX = nullptr;
WNDPROC UIX::ogWndProc = nullptr;

LRESULT WINAPI UIX::WndProcUIX( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		default:
		{
			if ( pUIX )
			{
				auto vWindows = pUIX->GetNativeWindows();
				for ( auto pWindow : vWindows )
				{
					auto pCanvas = pWindow->GetCanvas();
					if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
						break;
				}
			}
		}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT WINAPI UIX::WndProcUIXSA( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
	//case WM_MOUSEMOVE:
	//case WM_LBUTTONDOWN:
	//case WM_LBUTTONUP:
	//{
	//	if ( pUIX )
	//	{
	//		auto vWindows = pUIX->GetNativeWindows();
	//		for ( auto pWindow : vWindows )
	//		{
	//			if ( pWindow->GetCanvas()->GetIsStandalone() )
	//			{
	//				switch ( msg )
	//				{
	//					case WM_MOUSEMOVE:
	//					{
	//						auto xWindow = pWindow->GetCanvas()->GetChildren();
	//						if ( std::dynamic_pointer_cast<Window>( xWindow )->IsMoving() )
	//						{
	//							auto mdp = std::dynamic_pointer_cast<Window>( xWindow )->GetMouseDownPos();
	//							POINT p{ 0 };
	//							GetCursorPos( &p );
	//							int newX = p.x - mdp.x;
	//							int newY = p.y - mdp.y;
	//							SetWindowPos( pWindow->GetHWND(), 0, newX, newY, 0, 0, SWP_NOSIZE );
	//							pWindow->SetPos( { newX, newY } );
	//						}
	//						break;
	//					}
	//				}
	//			}

	//			auto pCanvas = pWindow->GetCanvas();
	//			if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
	//				break;

	//		}
	//		break;
	//	}
	//}



	switch ( msg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		case WM_MOUSEMOVE:
		{
			auto vWindows = pUIX->GetNativeWindows();
			for ( auto pWindow : vWindows )
			{
				auto xWindow = pWindow->GetCanvas()->GetChildren();
				if ( std::dynamic_pointer_cast<Window>( xWindow )->IsMoving() )
				{
					auto mdp = std::dynamic_pointer_cast<Window>( xWindow )->GetMouseDownPos();
					POINT p{ 0 };
					GetCursorPos( &p );
					int newX = p.x - mdp.x;
					int newY = p.y - mdp.y;
					SetWindowPos( pWindow->GetHWND(), 0, newX, newY, 0, 0, SWP_NOSIZE );
					pWindow->SetPos( { newX, newY } );
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		{
			if ( pUIX )
			{
				auto vWindows = pUIX->GetNativeWindows();
				for ( auto pWindow : vWindows )
				{
					auto pCanvas = pWindow->GetCanvas();
					if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
					{
						if ( pCanvas->GetWindow() && msg == WM_LBUTTONDOWN )
						{
							if ( pCanvas->GetWindow()->IsMoving() )
								SetCapture( pWindow->GetHWND() );
						}
						else
						{
							if ( !pCanvas->GetWindow()->IsMoving() )
								ReleaseCapture();
						}
						break;
					}
				}
				break;
			}
		}
		default:
		{
			if ( pUIX )
			{
				auto vWindows = pUIX->GetNativeWindows();
				for ( auto pWindow : vWindows )
				{
					auto pCanvas = pWindow->GetCanvas();
					if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
						break;
				}
			}
		}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT WINAPI UIX::WndProcUIXIn( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
	if ( pUIX )
	{
		if ( pUIX->GetCanvas() )
			if ( pUIX->GetCanvas()->PostMsg( msg, wParam, lParam, nullptr ) )
				return TRUE;
	}
	return ogWndProc(hWnd, msg, wParam, lParam);
}

UIX::UIX( HINSTANCE hInstance )
{
	this->hInstance = hInstance;
	this->hWnd = NULL;
	this->bInternal = false;
	this->pCanvas = nullptr;
}

UIX::UIX( HINSTANCE hInstance, HWND hWnd )
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	this->bInternal = true;
	this->pCanvas = nullptr;
}

UIX::~UIX()
{
	CRender::Cleanup();
}

UIXPtr UIX::Create( HINSTANCE hInstance, bool bInternal )
{
	if ( bInternal )
	{
		auto hWnd = GetWindowFromPID( GetProcessId( GetCurrentProcess() ) );
		
		if ( !hWnd )
			return nullptr;

		pUIX = std::make_unique<UIX>( hInstance );
		return Create( hInstance, hWnd );
	}
	else
		return Create(hInstance, HWND(0));
}

UIXPtr UIX::Create( HINSTANCE hInstance, HWND hWnd )
{
	if(!hWnd)
		pUIX = std::make_unique<UIX>( hInstance );
	else
		pUIX = std::make_unique<UIX>( hInstance, hWnd );
	return pUIX;
}

UIXPtr UIX::Get()
{
	return pUIX;
}

RenderPtr UIX::GetRenderer()
{
	return pRender;
}

NativeWindowPtr UIX::CreateNativeWindow( vec2i pos, vec2ui size, bool bShow )
{
	auto pWindow = MakeNativeWindowPtr( hInstance, WndProcUIX );
	pWindow->SetPos( pos );
	pWindow->SetSize(size);
	
	if ( !vNativeWindows.size() )
		pWindow->SetStyle( WS_OVERLAPPEDWINDOW );
	else
		pWindow->SetStyle( WS_OVERLAPPEDWINDOW | WS_CHILD );

	pWindow->Create( bShow );
	vNativeWindows.push_back( pWindow );
	return pWindow;
}

WindowPtr UIX::CreateStandaloneWindow( vec2i pos, vec2ui size )
{
	auto pNativeWindow = MakeNativeWindowPtr( hInstance, WndProcUIXSA );
	pNativeWindow->SetPos( pos );
	pNativeWindow->SetSize( size );
	pNativeWindow->SetStyle( WS_POPUP );
	pNativeWindow->Create();
	vNativeWindows.push_back( pNativeWindow );
	InitializeRendererEx(); // hope this doesn't fail? :P
	//auto canvasSize = size;
	//canvasSize *= vec2ui(2);
	//pNativeWindow->GetCanvas()->SetSize( { (float)canvasSize.x, (float)canvasSize.y } );
	auto pCanvas = pNativeWindow->GetCanvas();
	pCanvas->SetIsStandalone( true );
	pCanvas->SetSize( vec2f( size.x - 1.0f, size.y - 1.0f ) );
	return pCanvas->MakeWindow();
}

bool UIX::InitializeRenderer()
{
	if ( !bInternal )
		return this->InitializeRendererEx();
	else
		return this->InitializeRendererIn();
}

bool UIX::InitializeRenderer( DevicePtr pD3dDevice )
{
	return this->InitializeRendererIn( pD3dDevice );
}

bool UIX::InitializeRendererEx()
{
	if ( vNativeWindows.size() )
	{
		auto pWindow = vNativeWindows[ 0 ];
		auto pDevice = CRender::CreateDeviceDX9( pWindow->GetHWND() );

		if ( !pDevice )
			return false;

		pRender = MakeRendererPtr( pDevice );
		pWindow->SetRenderer( pRender, true );

		for ( uint x = 1; x < vNativeWindows.size(); x++ )
		{
			pWindow = vNativeWindows[ x ];
			pWindow->SetRenderer( MakeRendererPtr( pDevice ) );
		}
		return true;
	}
	else
	{
		ErrorMsgBox( _T( "Need to create a window before initializing the renderer." ) );
		return false;
	}
}

bool UIX::InitializeRendererIn()
{
	DevicePtr pDevice = nullptr;
	// use some sort of hook or some shit to get the direct3d device
	return InitializeRenderer( pDevice );
}

bool UIX::InitializeRendererIn( DevicePtr pDevice )
{
	if ( !pDevice )
		return false;

	pRender = MakeRendererPtr( pDevice );
	return true;
}

NativeWindows UIX::GetNativeWindows()
{
	return vNativeWindows;
}

bool UIX::HiJackWndProc()
{
	ogWndProc = (WNDPROC)SetWindowLongPtr( hWnd, GWLP_WNDPROC, (uintptr_t)WndProcUIXIn );
	if ( !ogWndProc )
		return false;
	return true;
}

CanvasPtr UIX::CreateCanvas()
{
	if ( !pCanvas )
		this->pCanvas = MakeCanvasPtr( pRender );
	
	//dont really think i need this... 
	//since we're just using the canvas as a parent to everything else for posting messages
	D3DVIEWPORT9 pVP{ 0 };
	pRender->GetDevice()->GetViewport( &pVP );
	pCanvas->SetSize( { (float)pVP.Width, (float)pVP.Height } );

	return pCanvas;
}

CanvasPtr UIX::GetCanvas()
{
	return pCanvas;
}

void UIX::RenderFrame()
{
	if ( !bInternal )
		RenderFrameEx();
	else
		RenderFrameIn();
}

void UIX::RenderFrameEx()
{
	for ( auto pWindow : vNativeWindows )
	{
		auto pRender = pWindow->GetRenderer();
		auto pDevice = pRender->GetDevice();

		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, UIX_DEFAULTBG, 1.0f, NULL );
		if ( pDevice->BeginScene() == S_OK )
		{
			auto pSurface = pWindow->SetAsRenderTarget();
			pWindow->GetCanvas()->PostMsg( WM_RENDER, 0, 0, 0 );
			pRender->Render();
			pDevice->EndScene();
			pWindow->GetSwapchain()->Present( 0, 0, pWindow->GetHWND(), 0, 0 );
			safe_release( pSurface );
		}
	}
}

void UIX::RenderFrameIn()
{
	if ( pCanvas )
		pCanvas->PostMsg( WM_RENDER, 0, 0, 0 );
	
	if ( pRender )
		pRender->Render();
}

void UIX::Cleanup()
{
}

