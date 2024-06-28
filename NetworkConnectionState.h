#pragma once
#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkConnectionState : public NetworkBaseState
	{
		private :
			void SendConnectionRequest(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port);
			void HandleConnectionResponse();
			void HandleConnectionRequest();
			void HandleConnectionAccepted();
			void HandleConnectionRefused();
			void HandleConnectionClosed();
			void HandleConnectionLost();
			void HandleConnectionTimeout();
			void HandleConnectionError();
			void HandleConnectionUnknown();

			//sf::UdpSocket socket;
			sf::IpAddress ip;
			unsigned short port;
			sf::Packet packet;
			sf::Packet connectionPacket;

		public:
			NetworkConnectionState();
			~NetworkConnectionState();

			void Init() override;
			void Update(float deltaTime) override;
			void Exit() override;

	};
}

