#pragma once
#include "Render\Render.h"
#include "Controls\Controls.h"
#include "misc\NativeWindow.h"
#include "misc\utility.h"
#include "Memory\Memory.h"

using NativeWindows = std::vector<NativeWindowPtr>;

class UIX;
using UIXPtr = std::shared_ptr<UIX>;

class UIX
{
	HINSTANCE hInstance;
	RenderPtr pRender;
	NativeWindows vNativeWindows;
	HWND hWnd;
	bool bInternal;
	CanvasPtr pCanvas;
	Color colClear;
public:
	UIX( HINSTANCE hInstance );
	UIX( HINSTANCE hInstance, HWND hWnd );
	~UIX();
	static UIXPtr Create( HINSTANCE hInstance, bool bInternal = false );
	static UIXPtr Create( HINSTANCE hInstance, HWND hWnd = NULL );
	static UIXPtr Get();
	RenderPtr GetRenderer();

	// only used in external/standalone apps
	NativeWindowPtr CreateNativeWindow( vec2i pos, vec2ui size, bool bShow = true );
	WindowPtr CreateStandaloneWindow( vec2i pos, vec2ui size );
	NativeWindowPtr CreateOverlayWindow( tstring szProcessName );
	NativeWindows GetNativeWindows();
	NativeWindowPtr GetNativeWindowByHandle( HWND hWnd );

	bool InitializeRenderer();
	bool InitializeRenderer(DevicePtr pD3dDevice);
private:
	bool InitializeRendererEx();
	bool InitializeRendererIn();
	bool InitializeRendererIn(DevicePtr pDevice);

public:
	bool HiJackWndProc();
	CanvasPtr CreateCanvas();
	CanvasPtr GetCanvas();
	void RenderFrame();
private:
	void RenderFrameEx();
	void RenderFrameIn();


public:
	void Cleanup();

	static LRESULT WINAPI WndProcUIX( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); // external
	static LRESULT WINAPI WndProcUIXSA( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); // standalone
	static LRESULT WINAPI WndProcUIXIn( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); //internal
private:
	static UIXPtr pUIX;
	static WNDPROC ogWndProc;
};
