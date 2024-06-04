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
			std::cerr << "Failed to bind the socket" << std::endl;
		}
		_socket.setBlocking(false);

		std::cout << "Host state initialized" << std::endl;

	}

	void NetworkHostState::Update(float deltaTime)
	{
		std::cout << "Update Network Host State" << std::endl;

		//std::lock_guard<std::mutex> lock(_mutex); // Lock the mutex to prevent simultaneous access to the socket from multiple threads
		CheckForNewConnections();
		ReceiveDataFromClients();

		// Check for new connections
		// Check for new messages
		// Send messages
		// Disconnect clients
	}

	void NetworkHostState::Exit()
	{
		std::cout << "Exiting Network Host State" << std::endl;

		_socket.unbind();

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

		const sf::Socket::Status status = _socket.receive(packet, ip, port);

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

		sf::Packet responsePacket;
		responsePacket << static_cast<sf::Int32>(NetworkPacketType::ACCEPTED);


		SendDataToClient(ip, port, responsePacket);

		std::cout << "Client connected : " << ip.toString() << " : " << port << std::endl;

	

		//while(_socket.receive(packet, ip, port) == sf::Socket::Done)
		//{
		//	std::cout << "Received a packet from : " << ip.toString() << " : " << port << std::endl;

		//	if (packet.endOfPacket()) {
		//		std::cout << "Received an empty packet or improperly formatted packet." << std::endl;
		//		continue; // Skip this iteration if the packet is empty or corrupted.
		//	}

		//	sf::Int32 packetType;
		//	if (!(packet >> packetType)) { // Read the packet type from the packet
		//		std::cout << "Failed to read packet type" << std::endl;
		//		continue;
		//	}

		//	


		//	// Check if the client is already connected
		//	//if (NetworkManager::GetInstance().IsClientConnected(ip, port))
		//	//{
		//	//	//std::cout << "Client already connected" << std::endl;
		//	//	return;
		//	//}

		//	// Add the client to the list
		//	NetworkManager::GetInstance().AddClient(ip, port);

		//	sf::Packet responsePacket;
		//	responsePacket << static_cast<sf::Int32>(NetworkPacketType::ACCEPTED);

		//	SendDataToClient(ip, port, responsePacket);

		//	std::cout << "Client connected : " << ip.toString() << " : " << port << std::endl;
		//}

		

	}

	void NetworkHostState::SendDataToAllClients(sf::Packet packet)
	{
		for (auto& client : NetworkManager::GetInstance().GetClients())
		{
			std::cout << "Sending data to : " << client.ip.toString() << " : " << client.port << std::endl;
			 _socket.send(packet, client.ip, client.port);
		}
	}

	void NetworkHostState::ReceiveDataFromClients()
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		if (_socket.receive(packet, ip, port) != sf::Socket::Done)
		{
			return;
		}

		// Check if the client is connected
	/*	if (!NetworkManager::GetInstance().IsClientConnected(ip, port))
		{
			return;
		}*/

		sf::Int32 dataType;
		packet >> dataType;

		if (dataType != static_cast<sf::Int32>(NetworkPacketType::ENTITIES))
		{
			return;
		}

		std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
		memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector

		auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities(); // Get the entities from the current scene

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			if (it->second->GetComponent<NetworkingComponent>() != nullptr)
			{
				it->second->Deserialize(data.data());
			}
		}
	}

	void NetworkHostState::SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet)
	{
		std::cout << "Sending data to : " << address.toString() << " : " << port << std::endl;
		_socket.send(packet, address, port);
	}

	

}
