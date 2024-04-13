#include "pch.h"
#include "NetworkHostState.h"

#include "NetworkManager.h"
#include "NetworkPacketType.h"

namespace LeaderEngine
{
	NetworkHostState::NetworkHostState()
	{
		std::cout << "Host state created" << std::endl;
	}

	NetworkHostState::~NetworkHostState()
	{
	}

	void NetworkHostState::Init()
	{
		std::cout << "Initializing host state" << std::endl;
		//NetworkManager::GetInstance().SetIp(sf::IpAddress::getLocalAddress());
		//NetworkManager::GetInstance().SetPort(5000);
		if(_socket.bind(5001) != sf::Socket::Done)
		{
			std::cout << "Failed to bind the socket" << std::endl;
			//;
		}
		_socket.setBlocking(false);

		std::cout << "Host state initialized" << std::endl;

	}

	void NetworkHostState::Update()
	{
		CheckForNewConnections();

		// Check for new connections
		// Check for new messages
		// Send messages
		// Disconnect clients
	}

	void NetworkHostState::Exit()
	{
		_socket.unbind();

		// TODO : Set a new host if the current host is disconnected
	}

	void NetworkHostState::CheckForNewConnections()
	{
		char data[100];
		std::size_t received;

		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		//std::cout << "Checking for new connections" << std::endl;

		//if (_socket.receive(packet, ip, port) != sf::Socket::Done)
		//{
		//	//std::cout << "Failed to receive data" << std::endl;
		//} else {
		//	std::cout << "Received a packet from : " << ip.toString() << " : " << port << std::endl;
		//}

		while(_socket.receive(packet, ip, port) == sf::Socket::Done)
		{
			std::cout << "Received a packet from : " << ip.toString() << " : " << port << std::endl;

			if (packet.endOfPacket()) {
				std::cout << "Received an empty packet or improperly formatted packet." << std::endl;
				continue; // Skip this iteration if the packet is empty or corrupted.
			}

			sf::Int32 packetType;
			if (!(packet >> packetType)) { // Read the packet type from the packet
				std::cout << "Failed to read packet type" << std::endl;
				continue;
			}

			if (packetType != static_cast<sf::Int32>(NetworkPacketType::CONNECT)) // Check if the packet type is a connection request
			{
				std::cout << "Invalid packet type" << std::endl;
				std::cout << "Packet type : " << packetType << std::endl;
				continue;
			}

			// Check if the client is already connected
			if (NetworkManager::GetInstance().IsClientConnected(ip, port))
			{
				std::cout << "Client already connected" << std::endl;
				return;
			}

			// Add the client to the list
			NetworkManager::GetInstance().AddClient(ip, port);

			sf::Packet responsePacket;
			responsePacket << static_cast<sf::Int32>(NetworkPacketType::ACCEPTED);

			SendDataToClient(ip, port, responsePacket);

			std::cout << "Client connected : " << ip.toString() << " : " << port << std::endl;
		}

		

	}

	void NetworkHostState::SendDataToAllClients(sf::Packet packet)
	{
		for (auto& client : NetworkManager::GetInstance().GetClients())
		{
			 _socket.send(packet, client.ip, client.port);
		}
	}

	void NetworkHostState::ReceiveDataFromClients()
	{
	//	sf::Packet packet;
	//	sf::IpAddress ip;
	//	unsigned short port;

	//	if (_socket.receive(packet, ip, port) != sf::Socket::Done)
	//	{
	//		return;
	//	}

	//	// Check if the client is connected
	///*	if (!NetworkManager::GetInstance().IsClientConnected(ip, port))
	//	{
	//		return;
	//	}*/

	//	std::string dataType;
	//	packet >> dataType;

	//	if (dataType != "Entities")
	//	{
	//		return;
	//	}

	//	std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
	//	memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector

	//	auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities();

	//	for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
	//	{
	//		if (it->second->GetComponent<NetworkingComponent>() != nullptr)
	//		{
	//			it->second->Deserialize(data.data());
	//		}
	//	}
	}

	void NetworkHostState::SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet)
	{
		_socket.send(packet, address, port);
	}

	

}
