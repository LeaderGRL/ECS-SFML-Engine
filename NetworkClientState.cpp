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

		flatbuffers::FlatBufferBuilder builder;
		auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities(); // Reference to the entities map in the entity manager

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			if (it->second->GetComponent<NetworkingComponent>() != nullptr)
			{
				sf::Packet packet = sf::Packet();
				std::string dataType = "Entities";
				packet << dataType;
				it->second->Serialize(builder);
				auto data = builder.GetBufferPointer(); // Get the data from the builder
				auto size = builder.GetSize(); // Get the size of the data
				packet.append(data, size); // Append the data to the packet to send it over the network
			}
		}

		ReceivePacket();
	}

	void NetworkClientState::Exit()
	{
		socket.unbind();
	}
}
