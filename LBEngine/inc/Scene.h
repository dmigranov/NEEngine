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
	void Render();

	void SetCamera(Entity* pCamera);
	Entity* GetCamera();

	void SetCameraOutputSize(double width, double height);

private:
	std::vector<Entity *>	m_entities;
	std::vector<System*>	m_systems;
	//std::list<const Light*>	m_lights;

	Entity* m_pCamera;
};

