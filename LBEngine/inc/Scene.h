#pragma once
#include <list>

class Entity;
class Light;
class System;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();
	void AddEntity(Entity* pEntity);
	//void AddLight(Light* pLight);

	void Update();

	void SetCamera(Camera* pCamera);
	Camera* GetCamera();

private:
	std::vector<Entity *>	m_entities;
	std::vector<System*>	m_systems;
	//std::list<const Light*>	m_lights;

	Camera* m_pCamera;
};

