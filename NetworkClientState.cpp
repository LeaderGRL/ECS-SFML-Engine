#include "pch.h"
#include "NetworkClientState.h"

#include "NetworkManager.h"
#include "NetworkPacketType.h"

namespace LeaderEngine
{
	NetworkClientState::NetworkClientState()
	{
		std::cout << "NetworkClientState created" << std::endl;
	}

	NetworkClientState::~NetworkClientState()
	{
	}

	void NetworkClientState::Init()
	{
		if (socket.bind(5003, sf::IpAddress::getLocalAddress()) != sf::Socket::Done)
		{
			std::cout << "Failed to bind the socket" << std::endl;
			//return;
		}
		socket.setBlocking(false);

	}

	void NetworkClientState::Update(float deltaTime)
	{
		std::cout << "Update Network Client State" << std::endl;

		flatbuffers::FlatBufferBuilder builder;
		auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities(); // Reference to the entities map in the entity manager

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			if (it->second->GetComponent<NetworkingComponent>() != nullptr)
			{
				sf::Packet packet = sf::Packet();
				sf::Int32 dataType = static_cast<sf::Int32>(NetworkPacketType::ENTITIES);
				packet << dataType;
				it->second->Serialize(builder);
				auto data = builder.GetBufferPointer(); // Get the data from the builder
				auto size = builder.GetSize(); // Get the size of the data
				packet.append(data, size); // Append the data to the packet to send it over the network

				SendPacket(packet, NetworkManager::GetInstance().GetIp(), 5001);
			}
		}

		ReceivePacket();
	}

	void NetworkClientState::Exit()
	{
		std::cout << "Exiting Network Client State" << std::endl;
		socket.unbind();
	}

	void NetworkClientState::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		std::cout << "Sending data to server" << std::endl;
		socket.send(packet, ip, port);
	}

	void NetworkClientState::ReceivePacket()
	{
		std::cout << "Receiving data from server" << std::endl;

		if (socket.receive(packet, ip, port) != sf::Socket::Done)
		{
			return;
		}

		 
	}
}
