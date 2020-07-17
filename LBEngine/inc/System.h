#pragma once
#include <vector>

#include "ComponentType.h"
#include <bitset>

class Entity;
class System
{
public:
	System() {};
	virtual ~System() {};
	virtual void Execute(double deltaTime) {};
protected:
	void SubscribeToComponentType(ComponentType ct);
	std::vector<Entity *> m_entities;;
	std::bitset<COMPONENT_TYPE_COUNT> m_componentsMask;

	friend class Scene;
private:
	const std::bitset<COMPONENT_TYPE_COUNT>& GetComponentsMask();
	void AddEntity(Entity * pEntity);
};

