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
		if(NetworkManager::GetInstance().GetSocket().bind(5001) != sf::Socket::Done)
		{
			std::cerr << "Failed to bind the socket" << std::endl;
		}
		NetworkManager::GetInstance().GetSocket().setBlocking(false);

		std::cout << "Host state initialized" << std::endl;

		NetworkManager::GetInstance().AddClient(NetworkManager::GetInstance().GetIp(), 5001); // Add the host as a client to the list of clients
		NetworkManager::GetInstance().SetUUID(NetworkManager::GetInstance().GetClientId(NetworkManager::GetInstance().GetIp(), 5001)); // Generate a unique ID for the host
	}

	void NetworkHostState::Update(float deltaTime)
	{
		//std::cout << "Update Network Host State" << std::endl;


		ReceiveDataFromClients();
		if (!NetworkManager::GetInstance().GetClients().empty())
			NetworkManager::GetInstance().BroadcastEntitiesPacket(); // Broadcast the entities to all clients
		CheckForNewConnections(); // We need to check for new connections after receiving data from clients to avoid having the CheckForNewConnections() function to receive the data packet sent by the new client

		
		

		// Check for new connections
		// Check for new messages
		// Send messages
		// Disconnect clients
	}

	void NetworkHostState::Exit()
	{
		std::cout << "Exiting Network Host State" << std::endl;

		NetworkManager::GetInstance().GetSocket().unbind();

		// TODO : Set a new host if the current host is disconnected
	}

	void NetworkHostState::CheckForNewConnections()
	{
		//std::lock_guard<std::mutex> lock(_mutex);
		//char data[100];
		//std::size_t received;
		
		sf::Packet packet;
		sf::IpAddress ip = sf::IpAddress::None;
		unsigned short port = 0;
		_connectionPacket = sf::Packet();

		const sf::Socket::Status status = NetworkManager::GetInstance().GetSocket().receive(packet, ip, port);

		if(status != sf::Socket::Done)
		{
			switch (status)
			{
				case sf::Socket::NotReady:
					std::cout << "No data received" << std::endl;
					break;
				case sf::Socket::Partial:
					std::cout << "Partial data received" << std::endl;
					break;
				case sf::Socket::Disconnected:
					std::cout << "Client disconnected" << std::endl;
					break;
				case sf::Socket::Error:
					std::cout << "An error occurred" << std::endl;
					break;
			}
			return;
		}



		std::cout << "Received a packet from : " << ip.toString() << " : " << port << std::endl;

		if (packet.endOfPacket()) {
			std::cout << "Received an empty packet or improperly formatted packet." << std::endl;
			return; // Skip this iteration if the packet is empty or corrupted.
		}

		sf::Int32 packetType;
		if (!(packet >> packetType)) { // Read the packet type from the packet
			std::cout << "Failed to read packet type" << std::endl;
			return;
		}

		


		// Check if the client is already connected
		if (NetworkManager::GetInstance().IsClientConnected(ip, port))
		{
			//std::cout << "Client already connected" << std::endl;
			return;
		}

		// Add the client to the list
		NetworkManager::GetInstance().AddClient(ip, port);
		std::cout << "Get Client ID : " << NetworkManager::GetInstance().GetClientId(ip, port) << std::endl;

		sf::Packet responsePacket;
		responsePacket << static_cast<sf::Int32>(NetworkPacketType::ACCEPTED);
		responsePacket << NetworkManager::GetInstance().GetClientId(ip, port);


		SendDataToClient(ip, port, responsePacket);

		std::cout << "Client connected : " << ip.toString() << " : " << port << std::endl;
	}

	void NetworkHostState::SendDataToAllClients(sf::Packet packet)
	{
		for (auto& client : NetworkManager::GetInstance().GetClients())
		{
			std::cout << "Sending data to : " << client.second.ip.toString() << " : " << client.second.port << std::endl;
			SendDataToClient(client.second.ip, client.second.port, packet);
		}
	}

	void NetworkHostState::ReceiveDataFromClients()
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		switch(NetworkManager::GetInstance().GetSocket().receive(packet, ip, port))
		{
			case sf::Socket::Done:
				std::cout << "RReceived a packet from : " << ip.toString() << " : " << port << std::endl;
				break;
			case sf::Socket::NotReady:
				std::cout << "No data received" << std::endl;
				return;
			case sf::Socket::Partial:
				std::cout << "Partial data received" << std::endl;
				return;
			case sf::Socket::Disconnected:
				std::cout << "Client disconnected" << std::endl;
				return;
			case sf::Socket::Error:
				std::cout << "An error occurred" << std::endl;
				return;
		}

		// Check if the client is connected
		if (!NetworkManager::GetInstance().IsClientConnected(ip, port))
		{
			std::cout << "Client not connected" << std::endl;
			return;
		}

		NetworkManager::GetInstance().HandleIncomingPackets(packet, ip, port);

	}

		//std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
		//memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector

	void NetworkHostState::SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet)
	{
		std::cout << "Sending data to : " << address.toString() << " : " << port << std::endl;
		NetworkManager::GetInstance().GetSocket().send(packet, address, port);
	}
		
}

