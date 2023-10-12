#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"
#include "System.h"

namespace LeaderEngine {
	class Application
	{
		private:
			sf::RenderWindow window;
			void Init();
			std::vector<Entity> entities;
			System system;
		protected :
		public : 
			Application();
			~Application();
			void Run();
			sf::RenderWindow& GetWindow();
			void Close();
	};

}
