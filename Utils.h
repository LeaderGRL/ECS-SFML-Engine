#pragma once
#include <SFML/Window.hpp>

namespace LeaderEngine
{
	class Utils
	{
		public :
			static int GetKeyEventCode(const sf::Event::KeyEvent& keyEvent);
			static int GetMouseEventCode(const sf::Event::MouseButtonEvent& mouseEvent);
	};
}
