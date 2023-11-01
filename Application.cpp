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
//#include <LuaBridge/LuaBridge.h>


namespace LeaderEngine {

	Application::Application() : window(sf::VideoMode(800, 600), "ECS Application")
	{
		//luabridge::getGlobalNamespace()
		Init();

	}

	Application::~Application()
	{
		
	}

	sf::RenderWindow& Application::GetWindow()
	{
		return window;
	}

	void Application::Init()
	{
		//ResourceManager rm;
		ResourceManager::GetInstance().LoadResource("Assets/Config/resources.yml");
		/*std::filesystem::path currentPath = std::filesystem::current_path();
		std::cout << "Current path is: " << currentPath.string() << std::endl;*/

		//const sf::Texture& texture = rm.getTexture("Leader");

		/*entityManager.CreateEntity("Fighter");
		entityManager.GetEntity("Fighter")->AddComponent<Sprite2DComponent>(ResourceManager::GetInstance().getTexture("Fighter"));
		entityManager.GetEntity("Fighter")->AddComponent<BoxColliderComponent>(sf::Vector2f(64,64));
		entityManager.GetEntity("Fighter")->setPosition(sf::Vector2f(200, 200));

		entityManager.CreateEntity("FighterEffect");
		entityManager.GetEntity("FighterEffect")->AddComponent<Sprite2DComponent>();
		entityManager.GetEntity("FighterEffect")->GetComponent<Sprite2DComponent>()->PlayAnimation("FighterEffectAnimation");
		entityManager.GetEntity("FighterEffect")->setPosition(sf::Vector2f(200, 200));*/
		
		//entityManager.CreateEntity("test");
		//entityManager.GetEntity("test")->AddComponent<Sprite2DComponent>(ResourceManager::GetInstance().getTexture("Leader"));
		////entityManager.GetEntity("test")->setScale(sf::Vector2f(0.2f, 0.2f));
		//entityManager.GetEntity("test")->GetComponent<Sprite2DComponent>()->SetSize(sf::Vector2f(300, 300));
		//entityManager.GetEntity("test")->setPosition(sf::Vector2f(200, 200));
		//entityManager.GetEntity("test")->AddComponent<BoxColliderComponent>(sf::Vector2f(300, 300));
		////entityManager.GetEntity("test")->setRotation(75.f);

		//entityManager.CreateEntity("oui");
		//entityManager.GetEntity("oui")->AddComponent<Sprite2DComponent>(ResourceManager::GetInstance().getTexture("Leader"));
		//entityManager.GetEntity("oui")->GetComponent<Sprite2DComponent>()->SetSize(sf::Vector2f(300, 300));
		//entityManager.GetEntity("oui")->setPosition(sf::Vector2f(480, 480));
		//entityManager.GetEntity("oui")->AddComponent<BoxColliderComponent>(sf::Vector2f(300, 300));

		//std::cout << collisionSystem.BoxOverlap(*entityManager.GetEntity("test"), *entityManager.GetEntity("oui")) <<std::endl;

		//Sprite2DComponent test("Assets\\blanket.png");
		/*Entity gameEntity;
		gameEntity.SetId(0);
		gameEntity.AddComponent(std::make_unique<Sprite2DComponent>("Assets\\blanket.png"));
		gameEntity.setRotation(35.f); 
		gameEntity.setScale(sf::Vector2f(0.2f, 0.2f));

		Entity gameEntity2;
		gameEntity2.SetId(1);
		gameEntity2.AddComponent(std::make_unique<Sprite2DComponent>("Assets\\blanket.png"));
		gameEntity2.setRotation(120.f);
		gameEntity2.setScale(sf::Vector2f(0.2f, 0.2f));
		gameEntity2.setPosition(sf::Vector2f(500.f, 200.f));


		Entity camera;
		camera.SetId(2);
		camera.AddComponent(std::make_unique<CameraComponent>());
		sf::View view = camera.GetComponent<CameraComponent>()->getView();
		view.rotate(180);*/

		
		//system.AddEntity(std::move(gameEntity));
		//system.AddEntity(std::move(gameEntity2));
		//system.AddEntity(std::move(camera));
		//window.setView(view);

	}  

	void Application::Run()
	{
		sf::Clock clock;
		LuaAPI luaAPI;

		while (window.isOpen())
		{
			
			sf::Event event;
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

