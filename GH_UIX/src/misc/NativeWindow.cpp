#include "stdafx.h"
#include "NativeWindow.h"


bool CNativeWindow::bRegistered = false;
CNativeWindow::CNativeWindow( HINSTANCE hInstance, WNDPROC pWndProc )
{
	this->hInstance = hInstance;
	this->pWndProc = pWndProc;
	this->iX = 0;
	this->iY = 0;
	this->uiWidth = 800;
	this->uiHeight = 600;
	this->dwStyle = 0;
	this->dwStyleEx = 0;
	this->pCanvas = nullptr;
	this->bIsOverlay = false;
	this->hOverlayTarget = NULL;
}


CNativeWindow::~CNativeWindow()
{
}

void CNativeWindow::SetTitle( tstring sTitle )
{
	this->sTitle = sTitle;
}

tstring CNativeWindow::GetTitle()
{
	return sTitle;
}

void CNativeWindow::SetPosX( int x )
{
	this->iX = x;
}

int CNativeWindow::GetPosX()
{
	return iX;
}

void CNativeWindow::SetPosY( int y )
{
	this->iY = y;
}

int CNativeWindow::GetPosY()
{
	return iY;
}

void CNativeWindow::SetPos( int x, int y )
{
	SetPosX( x );
	SetPosY( y );
}

void CNativeWindow::SetPos( vec2i pos )
{
	SetPos( pos.x, pos.y );
}

vec2i CNativeWindow::GetPos()
{
	return vec2i(iX, iY);
}

void CNativeWindow::SetWidth( uint w )
{
	this->uiWidth = w;
}

uint CNativeWindow::GetWidth()
{
	return uiWidth;
}

void CNativeWindow::SetHeight( uint h )
{
	this->uiHeight = h;
}

uint CNativeWindow::GetHeight()
{
	return uiHeight;
}

void CNativeWindow::SetSize( uint w, uint h )
{
	SetWidth( w );
	SetHeight( h );
}

void CNativeWindow::SetSize( vec2ui size )
{
	SetSize( size.x, size.y );
}

vec2ui CNativeWindow::GetSize()
{
	return vec2ui(uiWidth, uiHeight);
}

void CNativeWindow::SetStyle( DWORD dwStyle )
{
	this->dwStyle = dwStyle;
	SetWindowLongPtr( hWnd, GWL_STYLE, (LONG)dwStyle );
	SetWindowPos( hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}

DWORD CNativeWindow::GetStyle()
{
	return dwStyle;
}

void CNativeWindow::SetStyleEx( DWORD dwStyleEx )
{
	this->dwStyleEx = dwStyleEx;
	SetWindowLongPtr( hWnd, GWL_EXSTYLE, (LONG)dwStyleEx );
	SetWindowPos( hWnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}

DWORD CNativeWindow::GetStyleEx()
{
	return dwStyleEx;
}

void CNativeWindow::SetIsOverlay( bool bIsOverlay )
{
	this->bIsOverlay = bIsOverlay;
}

bool CNativeWindow::GetIsOverlay()
{
	return bIsOverlay;
}

void CNativeWindow::SetOverlayTarget( HWND hTarget )
{
	this->hOverlayTarget = hTarget;
}

HWND CNativeWindow::GetOverlayTarget()
{
	return this->hOverlayTarget;
}

HWND CNativeWindow::GetHWND()
{
	return hWnd;
}

HINSTANCE CNativeWindow::GetInstanceHandle()
{
	return hInstance;
}

bool CNativeWindow::Create( bool bShow /*=true*/ )
{
	if(!CNativeWindow::bRegistered)
		RegisterClassUIX();

	hWnd = CreateWindowEx( 
		dwStyleEx,
		UIXCLASS,
		sTitle.c_str(),
		dwStyle,
		iX, iY,
		uiWidth, uiHeight,
		NULL, NULL,
		hInstance,
		NULL );
	
	if(!hWnd)
	{
		LastErrorMsgBox( _T( "Failed to create window...\n" ) );
		return false;
	}

	if ( bIsOverlay )
	{
		SetLayeredWindowAttributes( hWnd, UIX_ALPHAKEY, 0, LWA_COLORKEY );
	}

	if(bShow)
		ShowWindow( hWnd, SW_SHOW );

	return true;
}

void CNativeWindow::SetRenderer( RenderPtr pRender, bool bCreateSwapchain )
{
	this->pRender = pRender;
	if ( bCreateSwapchain )
		CreateSwapchain();
	else
		pRender->GetDevice()->GetSwapChain( 0, &this->pSwapchain );

	if ( pCanvas )
		pCanvas->PostMsg( WM_SETRENDERER, 0, 0, &pRender );
	else
	{
		pCanvas = MakeCanvasPtr( pRender );
		pCanvas->SetSize( { (float)uiWidth, (float)uiHeight } );
	}
}

RenderPtr CNativeWindow::GetRenderer()
{
	return pRender;
}

void CNativeWindow::CreateSwapchain()
{
	D3DPRESENT_PARAMETERS pp{ 0 };
	pp.Windowed = TRUE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = hWnd;

	HRESULT result = CRender::pDeviceDX9->CreateAdditionalSwapChain( &pp, &pSwapchain );
	if ( result != D3D_OK )
		ErrorMsgBox( _T( "Failed to create additional swapchain." ) );
}

void CNativeWindow::SetSwapchain( SwapChainPtr pSwapchain )
{
	this->pSwapchain = pSwapchain;
}

SwapChainPtr CNativeWindow::GetSwapchain()
{
	return pSwapchain;
}

SurfacePtr CNativeWindow::SetAsRenderTarget()
{
	auto pDevice = this->pRender->GetDevice();
	pSwapchain->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pSurface );
	pDevice->SetRenderTarget( 0, pSurface );
	return pSurface;
}

CanvasPtr CNativeWindow::GetCanvas()
{
	return pCanvas;
}

void CNativeWindow::RegisterClassUIX()
{
	WNDCLASSEX wc{ 0 };

	wc.cbSize = sizeof( wc );
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = pWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = UIXCLASS;

	RegisterClassEx( &wc );

	CNativeWindow::bRegistered = true;
}
