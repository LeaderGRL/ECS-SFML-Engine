#pragma once
#include <mutex>

#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkHostState : public NetworkBaseState
	{
		private:
			sf::UdpSocket _socket;
			void CheckForNewConnections();
			void SendDataToAllClients(sf::Packet packet);
			void ReceiveDataFromClients();
			void SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet);
			sf::Packet _connectionPacket;
			std::mutex _mutex;



			


		public:
			NetworkHostState();
			~NetworkHostState() override;

			void Init() override;
			void Update(float deltaTime) override;
			void Exit() override;


					
	};
}

