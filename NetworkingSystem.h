#pragma once
#include <iostream>
#include <SFML/Network.hpp>
namespace LeaderEngine
{
	class NetworkingSystem
	{
		private:
			sf::UdpSocket socket;
			sf::IpAddress ip;
			unsigned short port;
		   	sf::Packet packet;
			bool isHost = false;


		public:
			NetworkingSystem();
			~NetworkingSystem();

			void Update();
			void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			void ReceivePacket();
	};
}

