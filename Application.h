#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace LeaderEngine {
	class Application
	{
	private:
		void run();
		sf::RenderWindow window;
		// RenderSystem render_system;
		void init();
	protected :
	public : 
		Application();
		~Application();
	};

}
