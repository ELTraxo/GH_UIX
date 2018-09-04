#include "stdafx.h"
#include "MemEx.h"

MemEx::MemEx( tstring szProcess )
{
	this->dwPID = NULL;
	this->hProcess = NULL;
	this->szProcess = szProcess;
}


MemEx::~MemEx()
{
	if ( hProcess )
		CloseHandle( hProcess );
}

bool MemEx::Open()
{
	if ( hProcess )
	{
		CloseHandle( hProcess );
		hProcess = NULL;
	}
	dwPID = GetProcessID( szProcess );
	if ( !dwPID )
	{
		LastErrorMsgBox( _T( "Failed to get process ID:\n" ) );
		return false;
	}

	hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwPID );
	if ( !hProcess )
	{
		LastErrorMsgBox( _T( "Failed to open process:\n" ) );
		return false;
	}

	return true;
}

DWORD MemEx::GetPID()
{
	return dwPID;
}
