#pragma once
#include "TypesUIX.h"

struct WndEnumData
{
	DWORD pid;
	HWND hWnd;
};

BOOL WINAPI WndEnumCallback( HWND hWnd, LPARAM lParam );
HWND GetWindowFromPID( DWORD dwPID );

DWORD GetProcessID( tstring szProcessName );
uintptr_t GetModuleBase( DWORD dwPID, tstring szModule );