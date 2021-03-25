#pragma once
#include <list>

class Entity;
class Light;
class System;
class Camera;
class Game;


class Scene
{
public:
	Scene();
	~Scene();
	void AddEntity(Entity* pEntity);
	//void AddLight(Light* pLight);

	void AddSystem(System* system);


	void Update(double delta);
	void Render();

	void SetCamera(Entity* pCamera);
	Entity* GetCamera();

	void SetCameraOutputSize(double width, double height);

	//в текущей реализации вызывается только один раз,
	//потому добавление новых энтитей в ходе работы программы невозможно
	void SynchronizeSystemsWithEntities();
private:
	void UpdateProjMatrix();

	std::vector<Entity *>	m_entities;
	std::vector<System *>	m_nonDrawingSystems;
	std::vector<System*>	m_drawingSystems;

	//std::list<const Light*>	m_lights;

	double m_width = -1, m_height = -1;

	Game& m_game;
	Entity* m_pCamera;
};

