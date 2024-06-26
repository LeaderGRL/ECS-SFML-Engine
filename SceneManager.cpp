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

	SceneManager& SceneManager::GetInstance()
	{
		static SceneManager instance;
		return instance;
	}

	void SceneManager::PushScene(std::unique_ptr<Scene> scene)
	{
		try
		{
			if (!_scenes.empty())
			{
				_scenes.top()->Pause(); // Pause the current scene before pushing a new one
			}

			_scenes.push(std::move(scene));
			_scenes.top()->Init();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	
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

	void SceneManager::ChangeScene(Scene* scene)
	{
		while (!_scenes.empty())
		{
			_scenes.pop();
		}

		PushScene(std::unique_ptr<Scene>(scene));
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return _scenes.top().get();
	}

	//std::unique_ptr<Scene> SceneManager::CreateScene()
	//{
	//	return std::make_unique<Scene>();
	//}

	Scene* SceneManager::CreateScene() {
		auto scene = std::make_unique<Scene>();
		Scene* ptr = scene.get();
		PushScene(std::move(scene));
		return ptr;
	}

	std::stack<std::unique_ptr<Scene>>& SceneManager::GetScenes()
	{
		return _scenes;
	}

	void SceneManager::Init()
	{
		if (!_scenes.empty())
		{
			_scenes.top()->Init();
		}
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
