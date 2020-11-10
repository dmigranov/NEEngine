#include "pch.h"
#include "Timer.h"

#include <ctime>

Timer::Timer()
{
	m_timerStart = timeGetTime();
	Reset();
}

Timer::~Timer()
{}

DWORD Timer::GetTimer()
{
	return timeGetTime();
}

DWORD Timer::GetMillisFromStart()
{
	return timeGetTime() - m_timerStart;
}

DWORD Timer::GetDelta()
{
	//todo
	return 0;
}

void Timer::Sleep(int ms)
{
	DWORD start = GetTimer();
	while (start + ms > GetTimer());
}

bool Timer::Stopwatch(int ms)
{
	if (timeGetTime() > m_stopwatchStart + ms) {
		m_stopwatchStart = GetTimer();
		return true;
	}
	return false;
}

void Timer::Reset()
{
	m_stopwatchStart = GetTimer();
}
