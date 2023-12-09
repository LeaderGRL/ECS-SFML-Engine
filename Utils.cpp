#include "pch.h"
#include "Utils.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

namespace LeaderEngine
{
	int Utils::GetKeyEventCode(const sf::Event::KeyEvent& keyEvent)
	{
		return static_cast<int>(keyEvent.code);
	}

	int Utils::GetMouseEventCode(const sf::Event::MouseButtonEvent& mouseEvent)
	{
		return static_cast<int>(mouseEvent.button);
	}

	bool Utils::RectIntersects(const sf::Rect<float>& rect1, const sf::Rect<float>& rect2) {
		return rect1.intersects(rect2);
	}
}

