#include "pch.h"
#include "Application.h"
#include "Sprite2DComponent.h"
#include "Entity.h"
#include "System.h"
#include "CameraComponent.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <filesystem>

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
		std::filesystem::path currentPath = std::filesystem::current_path();
		std::cout << "Current path is: " << currentPath.string() << std::endl;
		//Sprite2DComponent test("Assets\\blanket.png");
		Entity gameEntity;
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
		camera.GetComponent<CameraComponent>()->setView(sf::View(sf::FloatRect(10, 10, 10, 10)));
		
		system.AddEntity(std::move(gameEntity));
		system.AddEntity(std::move(gameEntity2));
		system.AddEntity(std::move(camera));
		//camera.GetComponent<CameraComponent>()->getPosition();

	}

	void Application::Run()
	{
		while (window.isOpen())
		{
			int i = 0;
			system.GetEntityById(0)->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
			system.GetEntityById(2)->GetComponent<CameraComponent>()->setRotation(i++);
			std::cout << system.GetEntityById(2)->GetComponent<CameraComponent>()->getPosition().x << std::endl;
			
			sf::Event event;
			while (window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Black);

			for (const Entity& entity : system.GetEntities())
			{
				entity.draw(window, sf::RenderStates::Default);
				entity.Update();
			}
			
			window.display();
		}
	}

	void Application::Close()
	{
		window.close();
	}

}

