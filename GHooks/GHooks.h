#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>


using _IHKCallback = LRESULT( CALLBACK * )( WPARAM wParam, LPARAM lParam );
extern _IHKCallback IHKCallback;


using _WPCallback = LRESULT( CALLBACK * )( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
extern _WPCallback WPCallback;

using _CBTCallback = LRESULT( CALLBACK * )( int nCode, WPARAM wParam, LPARAM lParam );
extern _CBTCallback CBTCallback;

using _GMCallback = LRESULT( CALLBACK * )( WPARAM wParam, MSG * pMsg );
extern _GMCallback GMCallback;

extern "C"
{
	__declspec( dllexport ) void WINAPI SetKeyboardHookCallback( _IHKCallback pCallback );
	__declspec( dllexport ) LRESULT CALLBACK InputHook_Keyboard( int nCode, WPARAM wParam, LPARAM lParam );
	__declspec( dllexport ) void WINAPI SetWndProcHookCallback( _WPCallback pCallback );
	__declspec( dllexport ) LRESULT CALLBACK WndProcHook( int nCode, WPARAM wParam, LPARAM lParam );
	__declspec( dllexport ) void WINAPI SetCBTHookCallback( _CBTCallback pCallback );
	__declspec( dllexport ) LRESULT CALLBACK CBTHook( int nCode, WPARAM wParam, LPARAM lParam );


	__declspec( dllexport ) void WINAPI SetGetMessageHookCallback( _GMCallback pCallback );
	__declspec( dllexport ) LRESULT CALLBACK GetMessageHook( int nCode, WPARAM wParam, LPARAM lParam );

	__declspec( dllexport ) void CALLBACK WinEventHook( HWINEVENTHOOK hWinEventHook, DWORD event, HWND hWnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsgEventTime );
}