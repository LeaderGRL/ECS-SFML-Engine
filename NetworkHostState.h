#pragma once
#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkHostState : NetworkBaseState
	{
		private:
			sf::UdpSocket socket;
			void CheckForNewConnections();
			void SendDataToAllClients(sf::Packet packet);
			void ReceiveDataFromClients();
			void SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet);
			


		public:
			NetworkHostState();
			~NetworkHostState();

			void Init() override;
			void Update() override;
			void Exit() override;


					
	};
}

