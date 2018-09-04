#include "stdafx.h"
#include "utility.h"
#include "misc\error.h"

BOOL WINAPI WndEnumCallback( HWND hWnd, LPARAM lParam )
{
	DWORD pid = 0;
	GetWindowThreadProcessId( hWnd, &pid );
	auto wed = *(WndEnumData*)lParam;
	if ( pid == wed.pid && GetWindow( hWnd, GW_OWNER ) == HWND(0))
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

DWORD GetProcessID( tstring szProcessName )
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );
	if ( hSnapshot == INVALID_HANDLE_VALUE )
	{
		LastErrorMsgBox( _T( "Failed to create snapshot:\n" ) );
		return 0;
	}

	PROCESSENTRY32 pe32{ 0 };
	pe32.dwSize = sizeof( pe32 );
	DWORD pid = 0;
	if ( Process32First( hSnapshot, &pe32 ) )
	{
		if ( !lstrcmp( pe32.szExeFile, szProcessName.c_str() ) )
		{
			CloseHandle( hSnapshot );
			return pe32.th32ProcessID;
		}
		while ( Process32Next( hSnapshot, &pe32 ) )
		{
			if ( !lstrcmp( pe32.szExeFile, szProcessName.c_str() ) )
			{
				pid = pe32.th32ProcessID;
				break;
			}
		}
	}
	CloseHandle( hSnapshot );
	return pid; // if this function fails, pid will be zero
}

uintptr_t GetModuleBase( DWORD dwPID, tstring szModule )
{
	if ( !dwPID )
	{
		ErrorMsgBox( _T( "Failed to supply a valid process ID to GetModuleBase." ) );
		return 0;
	}

	HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
	if ( !hSnap )
	{
		LastErrorMsgBox( _T( "Failed to create module snapshot:\n" ) );
		return 0;
	}

	MODULEENTRY32 me32{ 0 };
	me32.dwSize = sizeof( me32 );
	if ( Module32First( hSnap, &me32 ) )
	{
		if ( !lstrcmp( me32.szModule, szModule.c_str() ) )
			return (uintptr_t)me32.modBaseAddr;
		while ( Module32Next( hSnap, &me32 ) )
		{
			if ( !lstrcmp( me32.szModule, szModule.c_str() ) )
				return (uintptr_t)me32.modBaseAddr;
		}
	}

	return 0;
}
