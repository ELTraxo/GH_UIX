#include "GHooks.h"

_IHKCallback IHKCallback = nullptr;
_WPCallback WPCallback = nullptr;
_CBTCallback CBTCallback = nullptr;
_GMCallback GMCallback = nullptr;

void WINAPI SetKeyboardHookCallback( _IHKCallback pCallback )
{
	IHKCallback = pCallback;
}

LRESULT CALLBACK InputHook_Keyboard( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == HC_ACTION )
	{
		if ( IHKCallback )
			if ( IHKCallback( wParam, lParam ) )
				return 0;
	}
	return CallNextHookEx( NULL, nCode, wParam, lParam );
}

void WINAPI SetWndProcHookCallback( _WPCallback pCallback )
{
	WPCallback = pCallback;
}

LRESULT CALLBACK WndProcHook( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == HC_ACTION )
	{
		CWPSTRUCT* pCWP = (CWPSTRUCT*)lParam;
		if ( pCWP )
		{
			if ( pCWP->hwnd == FindWindow( L"SDL_app", NULL ) )
			{
				if ( WPCallback )
				{
					if ( WPCallback( pCWP->hwnd, pCWP->message, pCWP->wParam, pCWP->lParam ) )
						return 0;
				}
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void WINAPI SetCBTHookCallback( _CBTCallback pCallback )
{
	CBTCallback = pCallback;
}

LRESULT CALLBACK CBTHook( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode > 0 )
	{
		if ( nCode == 5 || nCode == 0 )
		{
			HWND overlay = FindWindow( _T( "SDL_app" ), NULL );
			if ( (HWND)wParam == overlay )
				return 1;
		}
		if ( CBTCallback )
		{
			if ( CBTCallback( nCode, wParam, lParam ) )
				return 0;
		}
	}
	return CallNextHookEx( NULL, nCode, wParam, lParam );
}

void WINAPI SetGetMessageHookCallback( _GMCallback pCallback )
{
	GMCallback = pCallback;
}

LRESULT CALLBACK GetMessageHook( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == HC_ACTION )
	{
		if ( GMCallback )
		{
			if ( GMCallback( wParam, (MSG*)lParam ) )
				return 0;
		}
	}
	return CallNextHookEx( NULL, nCode, wParam, lParam );
}

void CALLBACK WinEventHook( HWINEVENTHOOK hWinEventHook, DWORD event, HWND hWnd, LONG idObject, LONG idChild, DWORD idEventThread, DWORD dwmsgEventTime )
{
	if ( event == EVENT_OBJECT_LOCATIONCHANGE )
	{
		//
	}
}
