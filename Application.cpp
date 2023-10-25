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

namespace LeaderEngine {

	Application::Application() : window(sf::VideoMode(800, 600), "ECS Application")
	{
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
		
		entityManager.CreateEntity("test");
		entityManager.GetEntity("test")->AddComponent<Sprite2DComponent>(ResourceManager::GetInstance().getTexture("Leader"));
		//entityManager.GetEntity("test")->setScale(sf::Vector2f(0.2f, 0.2f));
		entityManager.GetEntity("test")->GetComponent<Sprite2DComponent>()->SetSize(sf::Vector2f(300, 300));
		entityManager.GetEntity("test")->setPosition(sf::Vector2f(200, 200));
		entityManager.GetEntity("test")->AddComponent<BoxColliderComponent>(sf::Vector2f(300, 300));
		//entityManager.GetEntity("test")->setRotation(75.f);
	

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
		while (window.isOpen())
		{
			
			sf::Event event;
			while (window.pollEvent(event))
			{
			
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Black);
			entityManager.draw(window, sf::RenderStates::Default);
			window.display();
		}
	}

	void Application::Close()
	{
		window.close();
	}

}

