#pragma once
class Entity;

class Component
{
public:
	Component();
	virtual ~Component() {};
	virtual void Initialize(Entity* pEntity);

protected:
	Entity * m_pEntity;
};

