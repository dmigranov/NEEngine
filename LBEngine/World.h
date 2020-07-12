#pragma once
#include <list>

class Entity;
class Light;
class Camera;

class World
{
public:
	World();
	~World();
	void AddEntity(Entity* pEntity);
	void AddLight(Light* pLight);

	void Update();
	void Render();

	void SetCamera(Camera* pCamera);
	Camera* GetCamera();

private:
	std::list<Entity *>	m_entities;
	//std::list<const Light*>	m_lights;
	Camera* m_pCamera;
};

