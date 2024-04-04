#pragma once
#include <SFML/Network/IpAddress.hpp>

namespace LeaderEngine
{
	struct ClientInfo
	{
		sf::IpAddress ip;
		unsigned short port;
	};
}
