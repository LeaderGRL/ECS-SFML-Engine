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
}
