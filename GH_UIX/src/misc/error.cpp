#include "stdafx.h"
#include "error.h"

tstring GetLastErrorMsg()
{
	void* pMsg = nullptr;
	DWORD dwError = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		0,
		dwError,
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
		(LPTSTR)&pMsg,
		0, 0 );

	int msgLen = lstrlen( (LPCTSTR)pMsg );
	tstring error = (LPCTSTR)pMsg;
	LocalFree( pMsg );
	return error;
}

void LastErrorMsgBox( tstring text )
{
	text += GetLastErrorMsg();
	MessageBox( NULL, text.c_str(), _T( "Error!" ), MB_ICONERROR | MB_OK );
}

void ErrorMsgBox( tstring text )
{
	MessageBox( NULL, text.c_str(), _T( "Error!" ), MB_ICONERROR | MB_OK );
}