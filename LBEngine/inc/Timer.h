#pragma once


class Timer
{
public:
	Timer();
	~Timer();
	DWORD GetTimer();
	DWORD GetMillisFromStart();
	DWORD GetDelta();

	void Sleep(int ms);
	bool Stopwatch(int ms);

private:
	DWORD m_timerStart;
	DWORD m_stopwatchStart;
	void Reset();

};

