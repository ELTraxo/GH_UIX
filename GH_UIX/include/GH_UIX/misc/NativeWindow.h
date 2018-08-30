#pragma once
#include "TypesUIX.h"
#include "error.h"
#include "../Render/Render.h"
#include "../Controls/Controls.h"

#define UIXCLASS _T("UIXCLASS")
#define UIX_DEFAULTBG 0xFF002864
#define UIX_ALPHAKEY 0xFFFF00FF

class CNativeWindow
{
	// window shit
	static bool bRegistered;
	HWND hWnd;
	HINSTANCE hInstance;
	WNDPROC pWndProc;
	int iX;
	int iY;
	uint uiWidth;
	uint uiHeight;
	DWORD dwStyle;
	DWORD dwStyleEx;
	tstring sTitle;

	//d3d shit
	RenderPtr pRender;
	SwapChainPtr pSwapchain;
	SurfacePtr pSurface;
	ControlPtr pCanvas;

public:
	CNativeWindow( HINSTANCE hInstance, WNDPROC pWndProc );
	~CNativeWindow();

	void SetTitle( tstring sTitle );
	tstring GetTitle();

	void SetPosX( int x );
	int GetPosX();
	void SetPosY( int y );
	int GetPosY();
	void SetPos( int x, int y );
	void SetPos( vec2i pos );
	vec2i GetPos();

	void SetWidth( uint w );
	uint GetWidth();
	void SetHeight( uint h );
	uint GetHeight();
	void SetSize( uint w, uint h );
	void SetSize( vec2ui size );
	vec2ui GetSize();

	void SetStyle( DWORD dwStyle );
	DWORD GetStyle();
	void SetStyleEx( DWORD dwStyleEx );
	DWORD GetStyleEx();

	HWND GetHWND();
	HINSTANCE GetInstanceHandle();

	bool Create(bool bShow=true);

	void SetRenderer( RenderPtr pRender, bool bCreateSwapchain=false );
	RenderPtr GetRenderer();
	void SetSwapchain( SwapChainPtr pSwapchain );
	SwapChainPtr GetSwapchain();
	SurfacePtr SetAsRenderTarget();
	ControlPtr GetCanvas();
private:
	void CreateSwapchain();
	void RegisterClassUIX();
};

using NativeWindow = CNativeWindow;
using NativeWindowPtr = std::shared_ptr<NativeWindow>;
#define MakeNativeWindowPtr(hInstance, pWndProc) \
std::make_shared<NativeWindow>(hInstance, pWndProc)