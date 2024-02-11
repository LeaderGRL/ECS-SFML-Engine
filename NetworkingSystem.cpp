#include "pch.h"
#include "NetworkingSystem.h"

namespace LeaderEngine
{
	NetworkingSystem::NetworkingSystem()
	{
		socket.bind(5000);
		socket.setBlocking(false);
		 
	}

	NetworkingSystem::~NetworkingSystem()
	{
	}

	void NetworkingSystem::Update()
	{

		//sf::Packet packet = sf::Packet();
		//packet << "Hello, world!";

		//SendPacket(packet, "localhost", 5000);
		//ReceivePacket();
	}

	void NetworkingSystem::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		std::cout << "Sending packet to " << ip << ":" << port << std::endl;
		socket.send(packet, ip, port);
	}

	void NetworkingSystem::ReceivePacket()
	{
		char data[100];
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;	
		while (socket.receive(packet, ip, port) == sf::Socket::Done)
		{
			std::cout << "Received packet from " << ip << ":" << port << std::endl;
			std::cout << "Packet size: " << packet.getDataSize() << std::endl;
			packet >> data;
			std::cout << "Packet data: " << data << std::endl;

		}
	}

}