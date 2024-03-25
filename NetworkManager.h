#pragma once
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

namespace LeaderEngine
{
	class NetworkManager
	{
		private :
			sf::IpAddress _ip;
			unsigned short _port;

		public:
			NetworkManager();
			~NetworkManager();

			NetworkManager GetInstance();

			void SetIp(sf::IpAddress ip);
			void SetPort(unsigned short port);
			sf::IpAddress GetIp() const;
			unsigned short GetPort() const;

			void Update();
			//void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			//void ReceivePacket();
	};
}
