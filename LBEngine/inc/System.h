#pragma once
#include <vector>

class Entity;
//todo: создать MoveSystem/UpdateSystem - для обновления положений?
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Execute() {};
protected:
	std::vector<Entity *> m_entities;;
};

