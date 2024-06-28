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
		if (NetworkManager::GetInstance().GetSocket().bind(5002, sf::IpAddress::getLocalAddress()) != sf::Socket::Done)
		{
			std::cout << "Failed to bind the socket" << std::endl;
			//return;
		}
		NetworkManager::GetInstance().GetSocket().setBlocking(false);

		connectionPacket = sf::Packet();
		//char data[100];
		//constexpr std::size_t size = 100;
		//connectionPacket.append(data, size);

		connectionPacket << static_cast<sf::Int32>(NetworkPacketType::CONNECT);
		std::cout << "Connection state initialized" << std::endl;
	}

	void NetworkConnectionState::Update(float deltaTime)
	{
		std::cout << "Update connection state" << std::endl;

		char data[100];
		std::size_t received;
		sf::Packet acceptedPacket;
		sf::IpAddress ip;
		unsigned short port;

		SendConnectionRequest(connectionPacket, NetworkManager::GetInstance().GetIp(), 5001);

		while (NetworkManager::GetInstance().GetSocket().receive(acceptedPacket, ip, port) == sf::Socket::Done)
		{
			sf::Int32 packetType;
			std::string UUID;
			//acceptedPacket >> packetType;

			std::cout << "Received packet" << std::endl;

			if (acceptedPacket.endOfPacket())
			{
				std::cout << "Received an empty packet or improperly formatted packet." << std::endl;
				continue; // Skip this iteration if the packet is empty or corrupted.
			}

			if (!(acceptedPacket >> packetType)) { // Read the packet type from the packet
				std::cout << "Failed to read packet type" << std::endl;
				continue;
			}

			if (packetType != static_cast<sf::Int32>(NetworkPacketType::ACCEPTED)) // Check if the packet type is a connection request
			{
				std::cout << "Invalid packet type" << std::endl;
				std::cout << "Packet type : " << packetType << std::endl;
				continue;
			}

			if (!(acceptedPacket >> UUID)) { // Read the UUID from the packet
				std::cout << "Failed to read UUID" << std::endl;
				continue;
			}

			std::cout << "Received UUID : " << UUID << std::endl;

			if (UUID.empty())
			{
				std::cout << "Invalid UUID" << std::endl;
				continue;
			}

			switch (packetType)
			{
				case static_cast<sf::Int32>(NetworkPacketType::ACCEPTED):
					//HandleConnectionAccepted();
					NetworkStateManager::GetInstance().PushState(std::make_shared<NetworkClientState>(UUID));
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
		NetworkManager::GetInstance().GetSocket().unbind();
		std::cout << "Exiting connection state" << std::endl;
		
	}

	void NetworkConnectionState::SendConnectionRequest(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		 // Send connection request to server
		NetworkManager::GetInstance().GetSocket().send(packet, ip, port);
		std::cout << "Sent connection request to " << ip << ":" << port << std::endl;
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
