#include "stdafx.h"
#include "XTimer.h"

LARGE_INTEGER CXTimer::liFreq{ 0 };

CXTimer::CXTimer()
{
	if ( liFreq.LowPart == 0 )
		QueryPerformanceFrequency( &CXTimer::liFreq );
	liStart = { 0 };
	liStop = { 0 };
}

CXTimer::~CXTimer()
{
}

void CXTimer::Start()
{
	QueryPerformanceCounter( &liStart );
}

float CXTimer::Tick()
{
	QueryPerformanceCounter( &liStop );
	return float( liStop.LowPart - liStart.LowPart ) / float( CXTimer::liFreq.LowPart );
}
