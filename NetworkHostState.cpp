#include "pch.h"
#include "NetworkHostState.h"

namespace LeaderEngine
{
	NetworkHostState::NetworkHostState()
	{
	}

	NetworkHostState::~NetworkHostState()
	{
	}

	void NetworkHostState::Init()
	{

	}

	void NetworkHostState::Update()
	{
		 // Check for new connections
		// Check for new messages
		// Send messages
		// Disconnect clients
	}

	void NetworkHostState::Exit()
	{
		 // Disconnect all clients
		// Close the server
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

		std::string message;
		packet >> message;

		if (message != "Connect")
		{
			return;
		}

		// Check if the client is already connected
		if (NetworkManager::GetInstance().IsClientConnected(ip.toString()))
		{
			return;
		}

		// Add the client to the list
		NetworkManager::GetInstance().AddClient(ip);
	}

	void NetworkHostState::SendDataToAllClients(sf::Packet packet)
	{
		for (auto& client : NetworkManager::GetInstance().GetClients())
		{
			 
		}
	}

}
