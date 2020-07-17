#pragma once


class Timer
{
public:
	Timer();
	~Timer();
private:
	DWORD m_timerStart;
	DWORD m_stopwatchStart;
	void Reset();

};

