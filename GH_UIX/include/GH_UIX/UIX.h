#pragma once
#include "Render\Render.h"
#include "Controls\Controls.h"
#include "misc\NativeWindow.h"
#include "misc\utility.h"
#include "Memory\Memory.h"

using _IHKCallback = LRESULT( CALLBACK * )( WPARAM wParam, LPARAM lParam );
//extern _IHKCallback IHKCallback;
using _SetKeyboardHookCallback = void( WINAPI* )( _IHKCallback pCallback );

using _WPCallback = LRESULT( CALLBACK * )( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
//extern _WPCallback WPCallback;
using _SetWndProcHookCallback = void( WINAPI* )( _WPCallback pCallback );

using _CBTCallback = LRESULT( CALLBACK * )( int nCode, WPARAM wParam, LPARAM lParam );
using _SetCBTHookCallback = void( WINAPI* )( _CBTCallback pCallback );

using _GMCallback = LRESULT( CALLBACK * )( WPARAM wParam, MSG * pMsg );
using _SetGetMessageCallback = void( WINAPI* )( _GMCallback pCallback );

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
	NativeWindowPtr CreateStandaloneWindow( vec2i pos, vec2ui size );
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
	RECT GetOverlayRect( HWND hTarget );
	void UpdateOverlayRect( NativeWindowPtr pNative, RECT & r );
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
	static LRESULT WINAPI WndProcUIXOL( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); // overlay
	static LRESULT WINAPI WndProcUIXSA( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); // standalone
	static LRESULT WINAPI WndProcUIXIn( HWND hWnd, uint msg, WPARAM wParam, LPARAM lParam ); //internal
private:
	static UIXPtr pUIX;
	static WNDPROC ogWndProc;
};
