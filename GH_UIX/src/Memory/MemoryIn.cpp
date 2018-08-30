#include "stdafx.h"
#include "Memory.h"

bool MemIn::WriteInt( void * pDest, int val )
{
	return MemIn::Write<int>((int*)pDest, val);
}

bool MemIn::ReadInt( void * pDest, int & buffer )
{
	return MemIn::Read<int>( (int*)pDest, &buffer );
}
