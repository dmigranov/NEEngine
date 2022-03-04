#pragma once
#include <list>

class Entity;
class Light;
class System;
class CameraComponent;
class Game;
class Sound;

class Scene
{
public:
	Scene();
	~Scene();
	void AddEntity(Entity* pEntity);
	//void AddLight(Light* pLight);

	void AddSystem(System* system);


	void Update(double delta);
	void Render(double delta);

	void SetCamera(Entity* pCamera, CameraComponent * pCameraComponent);
	Entity* GetCamera();

	//DirectX::SimpleMath::Matrix GetProj();
	//DirectX::SimpleMath::Matrix GetView();


	void SetCameraOutputSize(double width, double height);

	//в текущей реализации вызывается только один раз,
	//потому добавление новых энтитей в ходе работы программы невозможно
	void SynchronizeSystemsWithEntities();

	double GetWidth();
	double GetHeight();

	void AddAndPlayLoopedSound(Sound* sound);

	friend class Game;
private:
	void UpdateProjMatrix();

	std::vector<Entity *>	m_entities;
	std::vector<System *>	m_nonDrawingSystems;
	std::vector<System*>	m_drawingSystems;

	void ResetLoopedSounds();
	std::vector<Sound*>	m_loopingSounds;


	//std::list<const Light*>	m_lights;

	double m_width = -1, m_height = -1;

	//DirectX::SimpleMath::Matrix m_proj;

	Game& m_game;
	Entity* m_pCamera;
};

