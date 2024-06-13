#pragma once
#include <SFML/Network/IpAddress.hpp>

namespace LeaderEngine
{
	struct ClientInfo
	{
		std::string id;
		sf::IpAddress ip;
		unsigned short port;

		bool operator==(const ClientInfo& other) const {
			return id == other.id && ip == other.ip && port == other.port;
		}
	};


}
