#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "EntityManager.h"
#include "ResourceManager.h"
#include "CollisionSystem.h"

namespace LeaderEngine {
	class Application
	{
		private:
			sf::RenderWindow window;
			void Init();
			std::vector<Entity> entities;
			EntityManager entityManager;
			//CollisionSystem collisionSystem;
		protected :
		public : 
			Application();
			~Application();
			void Run();
			sf::RenderWindow& GetWindow();
			void Close();
	};

}
