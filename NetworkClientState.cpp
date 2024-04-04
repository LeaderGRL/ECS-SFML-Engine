#include "pch.h"
#include "NetworkClientState.h"

namespace LeaderEngine
{
	NetworkClientState::NetworkClientState()
	{
	}

	NetworkClientState::~NetworkClientState()
	{
	}

	void NetworkClientState::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		socket.send(packet, ip, port);
	}

	void NetworkClientState::ReceivePacket()
	{
		if (socket.receive(packet, ip, port) != sf::Socket::Done)
		{
			return;
		}
	}

	void NetworkClientState::Init()
	{
		socket.bind(5000);
	}

	void NetworkClientState::Update()
	{
		ReceivePacket();
	}

	void NetworkClientState::Exit()
	{
		socket.unbind();
	}
}
