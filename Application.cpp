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
		LuaAPI::GetInstance().LoadScript("Assets/Scripts/Config.lua");
		ResourceManager::GetInstance().LoadResource("Assets/Config/resources.yml");


		Entity* Weapons = EntityManager::GetInstance().CreateEntity("FighterWeapons");
		Weapons->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Weapons.lua");
		Entity* player = EntityManager::GetInstance().CreateEntity("Fighter");
		player->AddComponent<ScriptComponent, const char*>("Assets/Scripts/Player.lua"); // Load the script automaticaly

		
	}  
	
	void Application::Run()
	{
		sf::Clock clock;
		sf::Event event;

		while (window.isOpen())
		{
			sf::Time time = clock.getElapsedTime();

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
						break;
					case sf::Event::KeyReleased:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::KeyReleased, event);
						break;
					case sf::Event::MouseButtonPressed:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::MouseButtonPressed, event);
						break;
					case sf::Event::MouseButtonReleased:
						EventManager::GetInstance().InvokeEvent(INPUT_EVENT::MouseButtonReleased, event);
						break;
				}
			}


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

