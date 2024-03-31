#pragma once
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include "NetworkingSystem.h"
#include "ClientInfo.h""

namespace LeaderEngine
{
	class NetworkManager
	{
		private :
			sf::IpAddress _hostIp;
			std::vector<ClientInfo> _clientsInfo;
			unsigned short _port;
			NetworkingSystem _networkSystem;

		public:
			NetworkManager();
			~NetworkManager();

			static NetworkManager& GetInstance();

			void SetIp(sf::IpAddress ip);
			void SetPort(unsigned short port);
			sf::IpAddress GetIp() const;
			unsigned short GetPort() const;

			void AddClient(sf::IpAddress ip, unsigned short port);
			void RemoveClient(sf::IpAddress ip, unsigned short port);
			std::vector<ClientInfo> GetClients() const;
			bool IsClientConnected(sf::IpAddress ip, unsigned short port) const;

			void Update();
			//void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			//void ReceivePacket();
	};
}
