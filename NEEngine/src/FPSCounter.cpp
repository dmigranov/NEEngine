#include "pch.h"
#include "FPSCounter.h"

FPSCounter::FPSCounter()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
}

void FPSCounter::Update()
{
	m_totalFrameCount++;

	m_count++;
	DWORD endTime;
	if ((endTime = timeGetTime()) >= (m_startTime + 1000))
	{
		m_frameTime = (double)(endTime - m_startTime) / m_count;
		m_fps = m_count;
		m_count = 0;

		m_totalTime += (endTime - m_startTime);
		m_meanFPS = 1000. * m_totalFrameCount / m_totalTime;

		if (m_totalFrameCount > 1000)
		{
			m_totalFrameCount = 0;
			m_totalTime = 0.;
		}

		m_startTime = timeGetTime();
	}
}

unsigned int FPSCounter::GetFPS()
{
	return m_fps;
}

unsigned int FPSCounter::GetMeanFPS()
{
	return m_meanFPS;
}

double FPSCounter::GetFrameTime()
{
	return m_frameTime;
}
