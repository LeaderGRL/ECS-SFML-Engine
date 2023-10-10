#include "pch.h"
#include "Application.h"
#include "Sprite2DComponent.h"
#include "Entity.h"
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
		Sprite2DComponent test("Assets\\blanket.png");
		/*Entity gameEntity;*/
		gameEntity.SetId(0);
		gameEntity.AddSpriteComponent2D("Assets\\blanket.png");
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

			gameEntity.draw(window, sf::RenderStates::Default);
			window.display();
		}
	}

	void Application::Close()
	{
		window.close();
	}

}

