#include "stdafx.h"
#include "UIX.h"


UIXPtr UIX::pUIX = nullptr;
WNDPROC UIX::ogWndProc = nullptr;
LRESULT WINAPI UIX::WndProcUIXOL( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
	int x = 0;
	x += 1;
	switch ( msg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		case WM_NCHITTEST:
			return 0;
		case WM_INPUT:
		{
			UINT dwSize;

			GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
				sizeof( RAWINPUTHEADER ) );
			LPBYTE lpb = new BYTE[ dwSize ];
			if ( lpb == NULL )
			{
				return 0;
			}
			delete lpb;
			break;
		}
		case WM_MOUSEMOVE:
		{
			return 0;
			auto vWindows = pUIX->GetNativeWindows();
			for ( auto pWindow : vWindows )
			{
				auto xWindow = pWindow->GetCanvas()->GetChildren();
				if ( xWindow )
				{	// if the first child of a canvas isn't a window...
					if ( std::dynamic_pointer_cast<Window>( xWindow )->IsMoving() ) // this might be an issue.
					{
						xWindow->PostMsg( msg, wParam, lParam, nullptr );
						break;
					}
				}
			}
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		{
			if ( pUIX )
			{
				//auto vWindows = pUIX->GetNativeWindows();
				auto pWindow = pUIX->GetNativeWindowByHandle( hWnd );
				if ( pWindow )
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
							if ( pCanvas->GetWindow() )
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
					if ( pCanvas )
					{
						if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
							break;
					}
				}
			}
		}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT WINAPI UIX::WndProcUIX( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
		case WM_DESTROY:
		{
			PostQuitMessage( 0 );
			break;
		}
		case WM_INPUT:
		{
			UINT dwSize;

			GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,
				sizeof( RAWINPUTHEADER ) );
			LPBYTE lpb = new BYTE[ dwSize ];
			if ( lpb == NULL )
			{
				return 0;
			}
			delete lpb;
			break;
		}
		case WM_MOUSEMOVE:
		{
			auto vWindows = pUIX->GetNativeWindows();
			for ( auto pWindow : vWindows )
			{
				auto xWindow = pWindow->GetCanvas()->GetChildren();
				if ( xWindow )
				{	// if the first child of a canvas isn't a window...
					if ( std::dynamic_pointer_cast<Window>( xWindow )->IsMoving() ) // this might be an issue.
					{
						xWindow->PostMsg( msg, wParam, lParam, nullptr );
						break;
					}
				}
			}
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		{
			if ( pUIX )
			{
				//auto vWindows = pUIX->GetNativeWindows();
				auto pWindow = pUIX->GetNativeWindowByHandle( hWnd );
				if ( pWindow )
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
							if ( pCanvas->GetWindow() )
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
					if ( pCanvas )
					{
						if ( pCanvas->PostMsg( msg, wParam, lParam, nullptr ) )
							break;
					}
				}
			}
		}
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT WINAPI UIX::WndProcUIXSA( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam )
{
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
				if ( xWindow )
				{	// if the first child of a canvas isn't a window...
					if ( std::dynamic_pointer_cast<Window>( xWindow )->IsMoving() ) // this might be an issue.
					{
						auto mdp = std::dynamic_pointer_cast<Window>( xWindow )->GetMouseDownPos();
						POINT p{ 0 };
						GetCursorPos( &p );
						int newX = p.x - (int)mdp.x;
						int newY = p.y - (int)mdp.y;
						SetWindowPos( pWindow->GetHWND(), 0, newX, newY, 0, 0, SWP_NOSIZE );
						pWindow->SetPos( { newX, newY } );
					}
				}
			}
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		{
			if ( pUIX )
			{
				//auto vWindows = pUIX->GetNativeWindows();
				auto pWindow = pUIX->GetNativeWindowByHandle( hWnd );
				if ( pWindow )
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
							if ( pCanvas->GetWindow() )
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
	this->colClear = UIX_DEFAULTBG;
}

UIX::UIX( HINSTANCE hInstance, HWND hWnd )
{
	this->hInstance = hInstance;
	this->hWnd = hWnd;
	this->bInternal = true;
	this->pCanvas = nullptr;
	this->colClear = UIX_DEFAULTBG;
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

NativeWindowPtr UIX::CreateStandaloneWindow( vec2i pos, vec2ui size )
{
	auto pNativeWindow = MakeNativeWindowPtr( hInstance, WndProcUIXSA );
	pNativeWindow->SetPos( pos );
	pNativeWindow->SetSize( size );
	pNativeWindow->SetStyleEx( WS_EX_COMPOSITED | WS_EX_LAYERED ); // 
	pNativeWindow->SetIsOverlay( true );	    // 
	if(!vNativeWindows.size() )
		pNativeWindow->SetStyle( WS_POPUP );
	else
		pNativeWindow->SetStyle( WS_POPUP | WS_CHILD);
	pNativeWindow->SetClass( UIXCLASS );
	pNativeWindow->Create();
	vNativeWindows.push_back( pNativeWindow );
	if ( !pRender )
	{
		InitializeRendererEx(); // hope this doesn't fail? :P
		pNativeWindow->SetRenderer( pRender );
	}
	else
	{
		pNativeWindow->SetRenderer( pRender, true );
	}
	//auto canvasSize = size;
	//canvasSize *= vec2ui(2);
	//pNativeWindow->GetCanvas()->SetSize( { (float)canvasSize.x, (float)canvasSize.y } );
	auto pCanvas = pNativeWindow->GetCanvas();
	pCanvas->SetIsStandalone( true );
	pCanvas->SetSize( vec2f( size.x - 1.0f, size.y - 1.0f ) );
	return pNativeWindow;
}

NativeWindowPtr UIX::CreateOverlayWindow( tstring szProcessName )
{
	// find process
	DWORD pid = GetProcessID( szProcessName );
	if ( !pid )
	{
		tstring error = _T( "Failed to find process: " );
		error += szProcessName;
		error += _T("\nFailed with error:\n");
		LastErrorMsgBox( error );
		return nullptr;
	}

	// get window handle
	HWND hTargetWindow = GetWindowFromPID( pid );

	// Create the overlay window and profit?
	RECT r = GetOverlayRect( hTargetWindow );

	auto pNative = MakeNativeWindowPtr( hInstance, WndProcUIXOL );
	pNative->SetPos( { r.left, r.top } ); 
	pNative->SetSize( { (uint)r.right - (uint)r.left, (uint)r.bottom - (uint)r.top } ); // don't judge me, kthx
	pNative->SetStyleEx( WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST );
	pNative->SetStyle( WS_POPUP | WS_VISIBLE );
	pNative->SetIsOverlay( true );
	pNative->SetOverlayTarget( hTargetWindow );
	pNative->SetClass( _T( "UIXOVERLAY" ) );
	pNative->Create();

	//HRGN hRgn = CreateRectRgn( 0, 0, pNative->GetWidth(), pNative->GetHeight() );
	//SetWindowRgn( pNative->GetHWND(), hRgn, true );
	//GetWindowRgn( pNative->GetHWND(), hRgn );
	
	vNativeWindows.push_back( pNative );

	if ( !pRender )
		InitializeRendererEx();
	else
	{
		auto pDevice = pRender->GetDevice();
		pNative->SetRenderer( MakeRendererPtr(pDevice), true );
	}

	colClear = UIX_ALPHAKEY;

	auto pCanvas = pNative->GetCanvas();
	auto size = pNative->GetSize();
	//pCanvas->SetSize( { float(size.x), float(size.y) } );
	return pNative;
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

NativeWindowPtr UIX::GetNativeWindowByHandle( HWND hWnd )
{
	for ( auto pWindow : vNativeWindows )
		if ( pWindow->GetHWND() == hWnd )
			return pWindow;
	return NativeWindowPtr(nullptr);
}

RECT UIX::GetOverlayRect( HWND hTarget )
{
	RECT r{ 0 };
	GetWindowRect( hTarget, &r );
	RECT rClient{ 0 };
	GetClientRect( hTarget, &rClient );

	long diff = ( r.bottom - r.top ) - rClient.bottom;

	r.top += diff - 3;
	r.bottom -= 3;
	diff = ( r.right - r.left ) - rClient.right;

	r.left += ( diff / 2 );
	r.right -= ( diff / 2 );
	return r;
}

void UIX::UpdateOverlayRect( NativeWindowPtr pNative, RECT & r )
{
	pNative->SetPos( { r.left, r.top } );
	pNative->SetSize( { (uint)r.right - (uint)r.left, (uint)r.bottom - (uint)r.top } ); // don't judge me, kthx
	SetWindowPos( pNative->GetHWND(), NULL, pNative->GetPosX(), pNative->GetPosY(), pNative->GetWidth(), pNative->GetHeight(), SWP_FRAMECHANGED );
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

		pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, UIX_ALPHAKEY, 1.0f, NULL );
		
		if ( pDevice->BeginScene() == S_OK )
		{
			auto pSurface = pWindow->SetAsRenderTarget();
			pWindow->GetCanvas()->PostMsg( WM_RENDER, 0, 0, 0 );
			pRender->Render();
			pDevice->EndScene();
			pWindow->GetSwapchain()->Present( 0, 0, pWindow->GetHWND(), 0, 0 );
			
			//safe_release( pSurface );
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

