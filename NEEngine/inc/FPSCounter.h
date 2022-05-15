#pragma once
class FPSCounter
{
public: 
	FPSCounter();
	void Update();	//called each frame
	unsigned int GetFPS();
	double GetFrameTime();
private:
	unsigned int m_fps, m_count;
	double m_frameTime;
	DWORD m_startTime;

	size_t m_totalFrameCount = 0;
};

