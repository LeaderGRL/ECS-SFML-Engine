#pragma once
#include <SFML/Network/IpAddress.hpp>

namespace LeaderEngine
{
	struct ClientInfo
	{
		sf::IpAddress address;
		unsigned short port;
	};
}
