#pragma once
class Entity;

class Component
{
public:
	Component();
	virtual ~Component() {};
	virtual void Initialize(Entity* pEntity);
	virtual void Update() {};

protected:
	Entity * m_pEntity;
};

