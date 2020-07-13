#pragma once
#include <string>
class Effect
{
public:
	Effect();
	virtual ~Effect();
	void Initialize();
	void Deinitialize();
private:
	std::string		m_vsFileName;
	std::string		m_psFileName;

};

