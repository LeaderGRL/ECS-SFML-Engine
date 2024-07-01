#pragma once
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "NetworkingSystem.h"
#include "ClientInfo.h""
#include "NetworkHostState.h"

namespace LeaderEngine
{
	class NetworkManager
	{
		private :
			sf::IpAddress _hostIp;
			//std::vector<ClientInfo> _clientsInfo;
			unsigned short _port;
			NetworkingSystem _networkSystem;
			NetworkHostState _hostState;
			sf::UdpSocket _socket;
			std::string _UUID;

			std::unordered_map<std::string, ClientInfo> _clientsInfo;

			// Helper function to generate a unique key for unordered_map
			std::string GenerateKey(sf::IpAddress ip, unsigned short port) const {
				return ip.toString() + ":" + std::to_string(port);
			}

		public:
			NetworkManager();
			~NetworkManager();

			static NetworkManager& GetInstance();

			void SetIp(sf::IpAddress ip);
			sf::IpAddress GetIp();

			void SetPort(unsigned short port);
			unsigned short GetPort();

			std::string GetClientId(sf::IpAddress ip, unsigned short port);

			sf::UdpSocket& GetSocket();

			std::string GetUUID();
			void SetUUID(std::string uuid);
			std::string GetLastNElementsOfUUID(int n);

			void AddClient(sf::IpAddress ip, unsigned short port);
			void RemoveClient(std::string id, sf::IpAddress ip, unsigned short port);
			std::unordered_map<std::string, ClientInfo> GetClients();
			bool IsClientConnected(sf::IpAddress ip, unsigned short port);

			std::string GenerateClientId();

			void HandleIncomingPackets(sf::Packet& packet, const sf::IpAddress& sender, unsigned short senderPort);
			void HandleEntitiesPacket(sf::Packet& packet, const sf::IpAddress& sender, unsigned short senderPort);
			void BroadcastEntitiesPacket(const Entity& entity);
			//void HandleOutgoingPackets();

			sf::Packet CreateEntityPacket(const Entity& entity);

			void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			void SendEntityPacket(const Entity& entity, const sf::IpAddress ip, const unsigned short port);
			/*sf::Packet PackAllNetworkEntities();*/

			void Update(float deltaTime);
			//void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			//void ReceivePacket();
	};
}
