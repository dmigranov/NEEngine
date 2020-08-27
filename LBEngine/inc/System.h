#pragma once
#include <vector>
#include <boost/dynamic_bitset.hpp>

#include "ComponentType.h"

class Entity;
class System
{
public:
	System();
	virtual ~System() {};
	virtual void Execute(double deltaTime) {};
protected:
	void SubscribeToComponentType(ComponentType ct);
	std::vector<Entity *> m_entities;
	boost::dynamic_bitset<> m_componentsMask;
	boolean m_isDrawing = false;

	virtual void AddEntity(Entity* pEntity);
	friend class Scene;
private:
	const boost::dynamic_bitset<>& GetComponentsMask();
};

