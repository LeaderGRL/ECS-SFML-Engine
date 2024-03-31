#include "pch.h"
#include "Scene.h"

namespace LeaderEngine
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Init()
	{
		_entityManager.Init();
	}

	void Scene::Pause()
	{

	}

	void Scene::Resume()
	{

	}

	void Scene::Update(float deltaTime)
	{
		_entityManager.Update(deltaTime);
	}

	void Scene::Draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		_entityManager.draw(target, states);
	}

	void Scene::SetSceneID(const std::string& sceneID)
	{
		_sceneID = sceneID;
	}

	std::string Scene::GetSceneID() const
	{
		return _sceneID;
	}

	EntityManager& Scene::GetEntityManager()
	{
		return _entityManager;
	}
}
