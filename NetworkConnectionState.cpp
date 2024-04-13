#include "pch.h"
#include "NetworkConnectionState.h"

#include "NetworkClientState.h"
#include "NetworkManager.h"
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
		std::cout << "Initializing connection state..." << sf::IpAddress::getLocalAddress() << std::endl;
		if (socket.bind(5001, sf::IpAddress::getLocalAddress()) != sf::Socket::Done)
		{
			std::cout << "Failed to bind the socket" << std::endl;
			//return;
		}
		socket.setBlocking(false);

		connectionPacket = sf::Packet();
		char data[100];
		constexpr std::size_t size = 100;
		connectionPacket.append(data, size);

		connectionPacket << static_cast<sf::Int32>(NetworkPacketType::CONNECT);
		std::cout << "Connection state initialized" << std::endl;
	}

	void NetworkConnectionState::Update()
	{
		char data[100];
		std::size_t received;
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		SendConnectionRequest(connectionPacket, NetworkManager::GetInstance().GetIp(), 5001);

		if (socket.receive(data, 100, received, ip, port) == sf::Socket::Done)
		{
			sf::Int32 packetType;
			packet >> packetType;

			std::cout << "Received packet type : " << packetType << std::endl;

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
		socket.send(packet, ip, port);
		//std::cout << "Sent connection request to " << ip << ":" << port << std::endl;
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
