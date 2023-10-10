#include "pch.h"
#include "Application.h"
#include <SFML/Window.hpp>

namespace LeaderEngine {

	Application::Application()
	{
		sf::Window(sf::VideoMode(800, 600), "ECS Application");
	}

	Application::~Application()
	{
		
	}

	void Application::init()
	{
		
	}

	void Application::run()
	{
	}
}

