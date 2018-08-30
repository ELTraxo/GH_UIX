#pragma once

namespace MemIn
{
	// templated read/write functions
	template<class T>
	bool Read( T * dest, T * buffer )
	{
		if ( !dest || !buffer )
			return false;
		
		DWORD dwOld = NULL;
		if ( !VirtualProtect( dest, sizeof( T ), PAGE_EXECUTE_READWRITE, &dwOld ) )
			return false;

		if ( !memcpy_s( buffer, sizeof( T ), dest, sizeof( T ) ) )
			return false;

		VirtualProtect( dest, sizeof( T ), dwOld, nullptr );
		return true;
	}

	template<class T>
	bool Write( T * dest, T data )
	{
		if ( !dest )
			return false;

		DWORD dwOld = NULL;
		if ( !VirtualProtect( dest, sizeof( T ), PAGE_EXECUTE_READWRITE, &dwOld ) )
			return false;
		
		*dest = data;

		VirtualProtect( dest, sizeof( T ), dwOld, nullptr );
		return true;
	}

	// read/write wrappers
	bool WriteInt( void* pDest, int val );
	bool ReadInt( void* pDest, int& buffer );
}