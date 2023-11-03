#include "pch.h"
#include "Utils.h"

namespace LeaderEngine
{
	int Utils::GetKeyEventCode(const sf::Event::KeyEvent& keyEvent)
	{
		return static_cast<int>(keyEvent.code);
	}
}

