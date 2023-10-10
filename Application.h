#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Entity.h"

namespace LeaderEngine {
	class Application
	{
		private:
			sf::RenderWindow window;
			void Init();
		protected :
		public : 
			Application();
			~Application();
			void Run();
			sf::RenderWindow& GetWindow();
			void Close();
			Entity gameEntity;			
	};

}
