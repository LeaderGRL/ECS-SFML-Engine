#include "pch.h"
#include "SceneManager.h"

namespace LeaderEngine
{
	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{
		
	}

	void SceneManager::PushScene(std::unique_ptr<Scene> scene)
	{
		if(!_scenes.empty())
		{
			_scenes.top()->Pause(); // Pause the current scene before pushing a new one
		}

		_scenes.push(std::move(scene));
		_scenes.top()->Init();
	}

	void SceneManager::PopScene()
	{
		if(!_scenes.empty())
		{
			_scenes.pop();
		}
		if (!_scenes.empty())
		{
			_scenes.top()->Resume(); // Resume the scene that was paused
		}
	}

	void SceneManager::ChangeScene(std::unique_ptr<Scene> scene)
	{
		while (!_scenes.empty())
		{
			_scenes.pop();
		}

		PushScene(std::move(scene));
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return _scenes.top().get();
	}

	void SceneManager::Update(float deltaTime)
	{
		if (!_scenes.empty())
		{
			_scenes.top()->Update(deltaTime);
		}
	}

	void SceneManager::Draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		if (!_scenes.empty())
		{
			_scenes.top()->Draw(target, states);
		}
	}
}
