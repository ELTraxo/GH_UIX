#pragma once

struct WndEnumData
{
	DWORD pid;
	HWND hWnd;
};

BOOL WINAPI WndEnumCallback( HWND hWnd, LPARAM lParam );
HWND GetWindowFromPID( DWORD dwPID );