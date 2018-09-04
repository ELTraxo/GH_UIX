#include "InputHook.h"
IHKCallback _IHKCallback = nullptr;

void WINAPI SetKeyboardHookCallback( IHKCallback pCallback )
{
	_IHKCallback = pCallback;
}

LRESULT CALLBACK InputHook_Keyboard( int nCode, WPARAM wParam, LPARAM lParam )
{
	if ( nCode == 0 )
	{
		if ( _IHKCallback )
			if ( _IHKCallback( wParam, lParam ) )
				return 0;
	}
	return CallNextHookEx( NULL, nCode, wParam, lParam );
}
