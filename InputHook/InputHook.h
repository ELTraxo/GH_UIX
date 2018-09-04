#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>



using IHKCallback = LRESULT( CALLBACK * )( WPARAM wParam, LPARAM lParam );
extern IHKCallback _IHKCallback;

extern "C"
{
	__declspec( dllexport ) void WINAPI SetKeyboardHookCallback( IHKCallback pCallback );
	__declspec( dllexport ) LRESULT CALLBACK InputHook_Keyboard( int nCode, WPARAM wParam, LPARAM lParam );
}