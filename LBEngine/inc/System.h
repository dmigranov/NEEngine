#pragma once
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "Game.h"
#include "ComponentTypeManager.h"


class Entity;

class System
{
public:
	System();
	virtual ~System() {};
	virtual void Execute(double deltaTime) {};
protected:
	//void SubscribeToComponentType(ComponentType ct);

	template<typename T> void SubscribeToComponentType()
	{
		auto manager = Game::GetInstance().GetComponentTypeManager();
		boost::dynamic_bitset<> add(manager->GetComponentTypesCount());
		add[manager->template GetComponentTypeIndex<T>()] = 1;
		m_componentsMask |= add;
	}

	std::vector<Entity *> m_entities;
	boost::dynamic_bitset<> m_componentsMask;
	boolean m_isDrawing = false;

	virtual void AddEntity(Entity* pEntity);
	friend class Scene;
private:
	const boost::dynamic_bitset<>& GetComponentsMask();
};

