#include "pch.h"
#include "NetworkHostState.h"

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
		NetworkManager::GetInstance().SetIp(sf::IpAddress::getLocalAddress());
		NetworkManager::GetInstance().SetPort(5000);
		socket.setBlocking(false);
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
		socket.unbind();

		// TODO : Set a new host if the current host is disconnected
	}

	void NetworkHostState::CheckForNewConnections()
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		if (socket.receive(packet, ip, port) != sf::Socket::Done)
		{
			return;
		}

		sf::Int32 message;
		packet >> message;

		if (message != static_cast<sf::Int32>(NetworkPacketType::CONNECT))
		{
			return;
		}

		// Check if the client is already connected
		if (NetworkManager::GetInstance().IsClientConnected(ip, port))
		{
			return;
		}

		// Add the client to the list
		NetworkManager::GetInstance().AddClient(ip, port);

		sf::Packet responsePacket;
		responsePacket << static_cast<sf::Int32>(NetworkPacketType::ACCEPTED);

		SendDataToClient(ip, port, responsePacket);

		std::cout << "Client connected : " << ip.toString() << " : " << port << std::endl;

	}

	void NetworkHostState::SendDataToAllClients(sf::Packet packet)
	{
		for (auto& client : NetworkManager::GetInstance().GetClients())
		{
			 socket.send(packet, client.ip, client.port);
		}
	}

	void NetworkHostState::ReceiveDataFromClients()
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;

		if (socket.receive(packet, ip, port) != sf::Socket::Done)
		{
			return;
		}

		// Check if the client is connected
	/*	if (!NetworkManager::GetInstance().IsClientConnected(ip, port))
		{
			return;
		}*/

		std::string dataType;
		packet >> dataType;

		if (dataType != "Entities")
		{
			return;
		}

		std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
		memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector

		auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities();

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
		socket.send(packet, address, port);
	}

	

}
