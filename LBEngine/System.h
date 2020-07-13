#pragma once
#include <vector>

class Entity;
//todo: создать MoveSystem/UpdateSystem - для обновления положений?
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Update() {};
protected:
	std::vector<Entity *> entities;;
};

