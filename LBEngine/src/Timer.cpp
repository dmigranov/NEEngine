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
