#pragma once
class Entity;

class Component
{
public:
	Component();
	virtual ~Component();


protected:
	Entity * m_pEntity;
};

