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
		ReceiveDataFromClients();
		CheckForNewConnections(); // We need to check for new connections after receiving data from clients to avoid having the CheckForNewConnections() function to receive the data packet sent by the new client


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

		switch(_socket.receive(packet, ip, port))
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

		sf::Int32 dataType;

		if (!(packet >> dataType) || dataType != static_cast<sf::Int32>(NetworkPacketType::ENTITIES))
		{
			std::cerr << "Error: Invalid packet type or failed to read packet type." << std::endl;
			return;
		}

		const void* packetData = packet.getData();
		std::size_t packetSize = packet.getDataSize();

		if (packetData == nullptr || packetSize == 0)
		{
			std::cerr << "Error: Invalid packet data or size." << std::endl;
			return;
		}

		if (dataType == static_cast<sf::Int32>(NetworkPacketType::ENTITIES))
		{
			const uint8_t* data = static_cast<const uint8_t*>(packet.getData()) + sizeof(dataType); // Skip the dataType part
			size_t dataSize = packet.getDataSize() - sizeof(dataType);

			flatbuffers::Verifier verifier(static_cast<const uint8_t*>(data), dataSize);
			if (!VerifyEntitySchemaBuffer(verifier))
			{
				std::cerr << "Error: Buffer verification failed." << std::endl;
				return;
			}

			const LeaderEngine::EntitySchema* entity_schema = flatbuffers::GetRoot<LeaderEngine::EntitySchema>(data);
			if (!entity_schema)
			{
				std::cerr << "Error: Failed to get entity schema." << std::endl;
				return;
			}

			// Deserialize and process the entity
			auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities();
			for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
			{
				if (it->second->GetComponent<NetworkingComponent>() != nullptr)
				{
					// validate the buffer
					std::cout << "Deserializing entity : " << it->first << " : " << packetSize << std::endl;

					try {
						it->second->Deserialize(data);
					}
					catch (const std::exception& e) {
						std::cerr << "Exception during deserialization: " << e.what() << std::endl;
					}
				}
			}
		}

		//std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
		//memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector


		
	}

	void NetworkHostState::SendDataToClient(sf::IpAddress address, unsigned short port, sf::Packet packet)
	{
		std::cout << "Sending data to : " << address.toString() << " : " << port << std::endl;
		_socket.send(packet, address, port);
	}

	

}
