#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EventManager.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backends/SFML.hpp>

namespace LeaderEngine {
	class Application
	{
		private:
			sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "ECS Application");
			void Init();
			tgui::GuiSFML gui{ window }; // Create a GUI and attach it to the window
		protected :
		public : 
			Application();
			~Application();
			void Run();
			sf::RenderWindow& GetWindow();
			void Close();
	};

}
