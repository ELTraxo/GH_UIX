#pragma once
#include "misc\utility.h"
#include "misc\error.h"

class MemEx
{
	HANDLE hProcess;
	tstring szProcess;
	DWORD dwPID;
public:
	MemEx(tstring szProcess);
	~MemEx();
	
	bool Open();
	DWORD GetPID();
	template <class T>
	bool Read( void * pDest, T * buffer, uint size );

	template <class T>
	bool Write( void * pDest, T * buffer, uint size );

};

template<class T>
inline bool MemEx::Read( void * pDest, T * buffer, uint size )
{
	if ( !hProcess )
	{
		tstring error = _T( "Failed to read memory.\nNo open handle to process: " );
		error += szProcess;
		ErrorMsgBox( error );
		return false;
	}

	if ( !ReadProcessMemory( hProcess, pDest, buffer, size, nullptr ) )
		return false;
	
	return true;
}

template<class T>
inline bool MemEx::Write( void * pDest, T * buffer, uint size )
{
	if ( !hProcess )
	{
		tstring error = _T( "Failed to write memory.\nNo open handle to process: " );
		error += szProcess;
		ErrorMsgBox( error );
		return false;
	}

	if ( !WriteProcessMemory( hProcess, pDest, buffer, size, nullptr ) )
		return false;
	
	return true;
}
