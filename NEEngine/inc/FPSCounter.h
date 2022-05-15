#pragma once
class FPSCounter
{
public: 
	FPSCounter();
	void Update();	//called each frame
	unsigned int GetFPS();
	double GetFrameTime();

	unsigned int GetMeanFPS();
private:
	unsigned int m_fps, m_count, m_meanFPS;
	double m_frameTime;
	DWORD m_startTime;

	size_t m_totalFrameCount = 0;
	size_t m_totalTime = 0.;
};

