#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "CollisionSystem.h"
#include "EventManager.h"

namespace LeaderEngine {
	class Application
	{
		private:
			sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "ECS Application");
			void Init();
			std::vector<Entity> entities;
		protected :
		public : 
			Application();
			~Application();
			void Run();
			sf::RenderWindow& GetWindow();
			void Close();
	};

}
