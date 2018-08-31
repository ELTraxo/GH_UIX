#pragma once

class CXTimer
{
	static LARGE_INTEGER liFreq;
	LARGE_INTEGER liStart;
	LARGE_INTEGER liStop;
public:
	CXTimer();
	~CXTimer();
	void Start();
	float Tick();
};

