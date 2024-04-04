#pragma once
#include <SFML/Network/IpAddress.hpp>

namespace LeaderEngine
{
	struct ClientInfo
	{
		sf::IpAddress ip;
		unsigned short port;

		bool operator==(const ClientInfo& other) const {
			return ip == other.ip && port == other.port;
		}
	};


}
