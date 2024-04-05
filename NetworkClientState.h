#pragma once
#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkClientState : public NetworkBaseState
	{
		private :
			sf::UdpSocket socket;
			sf::IpAddress ip;
			unsigned short port;
			sf::Packet packet;
			bool isHost = false;

			void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			void ReceivePacket();

		public:
			NetworkClientState();
			~NetworkClientState();

			void Init() override;
			void Update() override;
			void Exit() override;
	};
}

