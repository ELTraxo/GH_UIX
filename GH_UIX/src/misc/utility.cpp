#include "stdafx.h"
#include "utility.h"

BOOL WINAPI WndEnumCallback( HWND hWnd, LPARAM lParam )
{
	DWORD pid = 0;
	GetWindowThreadProcessId( hWnd, &pid );
	auto wed = *(WndEnumData*)lParam;
	if ( pid == wed.pid )
	{
		( (WndEnumData*)lParam )->hWnd = hWnd;
		return 0;
	}
	return TRUE;
}

HWND GetWindowFromPID( DWORD dwPID )
{
	WndEnumData wed{ 0 };
	wed.pid = dwPID;
	EnumWindows( WndEnumCallback, (LPARAM)&wed );
	return wed.hWnd;
}
