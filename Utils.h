#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace LeaderEngine
{
	class Utils
	{
		public :
			static int GetKeyEventCode(const sf::Event::KeyEvent& keyEvent);
			static int GetMouseEventCode(const sf::Event::MouseButtonEvent& mouseEvent);
			static bool RectIntersects(const sf::Rect<float>& rect1, const sf::Rect<float>& rect2);
	};
}
