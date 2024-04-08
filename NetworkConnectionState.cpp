#include "pch.h"
#include "NetworkConnectionState.h"

#include "NetworkClientState.h"
#include "NetworkPacketType.h"
#include "NetworkStateManager.h"

namespace LeaderEngine
{
	NetworkConnectionState::NetworkConnectionState()
	{
	}

	NetworkConnectionState::~NetworkConnectionState()
	{
	}

	void NetworkConnectionState::Init()
	{

	}

	void NetworkConnectionState::Update()
	{
		 sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		if (socket.receive(packet, ip, port) == sf::Socket::Done)
		{
			sf::Int32 packetType;
			packet >> packetType;

			switch (packetType)
			{
				case static_cast<sf::Int32>(NetworkPacketType::ACCEPTED):
					HandleConnectionAccepted();
					break;
				case static_cast<sf::Int32>(NetworkPacketType::REFUSED):
					HandleConnectionRefused();
					break;
				default:
					break;
			}
		}
	}

	void NetworkConnectionState::Exit()
	{
		
	}

	void NetworkConnectionState::SendConnectionRequest(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		 // Send connection request to server
		packet << static_cast<sf::Int32>(NetworkPacketType::CONNECT);
		socket.send(packet, ip, port);
	}

	void NetworkConnectionState::HandleConnectionAccepted()
	{
		std::cout << "Connection accepted" << std::endl;
		NetworkStateManager::GetInstance().PushState(std::make_shared<NetworkClientState>());
	}

	void NetworkConnectionState::HandleConnectionRefused()
	{
		std::cout << "Connection refused" << std::endl;
	}


}
