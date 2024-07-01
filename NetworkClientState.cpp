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

	NetworkClientState::NetworkClientState(const std::string& UUID)
	{
		std::cout << "NetworkClientState created with UUID: " << UUID << std::endl;
		_UUID = UUID;
	}

	NetworkClientState::~NetworkClientState()
	{
	}

	void NetworkClientState::Init()
	{
		//if (_socket.bind(5002, sf::IpAddress::getLocalAddress()) != sf::Socket::Done)
		//{
		//	std::cout << "Failed to bind the socket" << std::endl;
		//	//return;
		//}
		NetworkManager::GetInstance().GetSocket().setBlocking(false);

	}

	void NetworkClientState::Update(float deltaTime)
	{
		std::cout << "Update Network Client State" << std::endl;

		flatbuffers::FlatBufferBuilder builder;
		auto& entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities(); // Reference to the entities map in the entity manager

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			auto* networkComponent = it->second->GetComponent<NetworkingComponent>();
			if (!networkComponent)
			{
				continue;
			}

			if (!networkComponent->GetDirty())
			{
				continue;
			}
			
			NetworkManager::GetInstance().SendEntityPacket(*it->second, NetworkManager::GetInstance().GetIp(), 5001);
			//NetworkManager::GetInstance().BroadcastEntitiesPacket(*it->second);

			networkComponent->SetDirty(false);
			
		}

		ReceivePacket();
	}

	void NetworkClientState::Exit()
	{
		std::cout << "Exiting Network Client State" << std::endl;
		NetworkManager::GetInstance().GetSocket().unbind();
	}

	void NetworkClientState::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		std::cout << "Sending data to server" << std::endl;
		NetworkManager::GetInstance().GetSocket().send(packet, ip, port);
	}

	void NetworkClientState::ReceivePacket()
	{
		std::cout << "Receiving data from server" << std::endl;

		if (NetworkManager::GetInstance().GetSocket().receive(_packet, _ip, _port) != sf::Socket::Done)
		{
			return;
		}
	}
}
