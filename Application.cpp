#include "pch.h"
#include "Application.h"
#include "Sprite2DComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "CameraComponent.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <filesystem>
#include "BoxColliderComponent.h"
#include "LuaAPI.h"
#include "ScriptComponent.h"
//#include <LuaBridge/LuaBridge.h>

namespace LeaderEngine {

	Application::Application() //: window(sf::VideoMode(800, 600), "ECS Application")
	{
		//luabridge::getGlobalNamespace()
		Init();

	}

	Application::~Application()
	{
		window.close();
	}

	sf::RenderWindow& Application::GetWindow()
	{
		return window;
	}

	void Application::Init()
	{
		LuaAPI::GetInstance().CPP_To_LUA();
		//ResourceManager rm;
		ResourceManager::GetInstance().LoadResource("Assets/Config/resources.yml");
		/*std::filesystem::path currentPath = std::filesystem::current_path();
		std::cout << "Current path is: " << currentPath.string() << std::endl;*/

		//const sf::Texture& texture = rm.getTexture("Leader");
		Entity* player = EntityManager::GetInstance().CreateEntity("Fighter");
		//std::cout << entityManager.GetEntity("Fighter") << std::endl;
		player->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Player.lua"); // Load the script automaticaly
	}  
	
	void Application::Run()
	{
		sf::Clock clock;
		sf::Event event;


		while (window.isOpen())
		{
			
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					// "close requested" event: we close the window
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::KeyPressed:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::KeyPressed, event);
						LuaAPI::GetInstance().GetLuaStack();
						break;
					case sf::Event::KeyReleased:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::KeyReleased, event);
						break;
				}
			}

			sf::Time time = clock.getElapsedTime();

			window.clear(sf::Color::Black);
			EntityManager::GetInstance().draw(window, sf::RenderStates::Default);
			EntityManager::GetInstance().Update(time.asMilliseconds());
			window.display();
		}
	}

	void Application::Close()
	{
		window.close();
	}

}

