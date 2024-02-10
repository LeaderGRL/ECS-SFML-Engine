#include "pch.h"
#include "NetworkingSystem.h"

namespace LeaderEngine
{
	NetworkingSystem::NetworkingSystem()
	{
		socket.bind(sf::Socket::AnyPort);
		socket.setBlocking(false);
		 
	}

	NetworkingSystem::~NetworkingSystem()
	{
	}

	void NetworkingSystem::Update()
	{
	}

	void NetworkingSystem::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		socket.send(packet, ip, port);
	}

	void NetworkingSystem::ReceivePacket()
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;	
		while (socket.receive(packet, ip, port) == sf::Socket::Done)
		{
			std::cout << "Received packet from " << ip << ":" << port << std::endl;
			std::cout << "Packet size: " << packet.getDataSize() << std::endl;
		}
	}

}