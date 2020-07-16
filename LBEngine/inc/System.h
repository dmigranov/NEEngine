#pragma once
#include <vector>

class Entity;
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Execute() {};

protected:
	std::vector<Entity *> m_entities;;
};

