#pragma once
#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkClientState : public NetworkBaseState
	{
		private :
			std::string _UUID;
			//sf::UdpSocket _socket;
			sf::IpAddress _ip;
			unsigned short _port;
			sf::Packet _packet;
			bool _isHost = false;

			void SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			void ReceivePacket();

		public:
			NetworkClientState();
			NetworkClientState(const std::string& UUID);
			~NetworkClientState();

			void Init() override;
			void Update(float deltaTime) override;
			void Exit() override;
	};
}

