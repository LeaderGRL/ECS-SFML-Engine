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

    int Utils::GetMouseEventPosX(const sf::Event::MouseButtonEvent& mouseEvent)
    {
		return mouseEvent.x;
    }

	int Utils::GetMouseEventPosY(const sf::Event::MouseButtonEvent& mouseEvent)
	{
		return mouseEvent.y;
	}

    bool Utils::RectIntersects(const sf::Rect<float>& rect1, const sf::Rect<float>& rect2) {
		return rect1.intersects(rect2);
	}


	void Utils::GuiAddWidget(tgui::Gui* gui, tgui::Widget::Ptr widget, const std::string& widgetName)
	{
		gui->add(widget, widgetName);
	}
}

