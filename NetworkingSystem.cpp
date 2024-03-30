#include "pch.h"
#include "NetworkingSystem.h"

#include "EntityManager.h"
#include "NetworkingComponent.h"
#include "NetworkManager.h"
#include "SceneManager.h"

namespace LeaderEngine
{
	NetworkingSystem::NetworkingSystem()
	{
		socket.bind(5000);
		socket.setBlocking(false);

		if ( sf::IpAddress::getLocalAddress().toString() == "10.70.10.7" )
		{
			isHost = true;
		}
		
	}

	NetworkingSystem::~NetworkingSystem()
	{

	}

	void NetworkingSystem::Update()
	{
		flatbuffers::FlatBufferBuilder builder;
		auto &entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities(); // Reference to the entities map in the entity manager

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			//for (auto& component : it->second->GetComponents()) // Iterate through the components of the entity
			//{
			//	auto serializable = dynamic_cast<ISerializable*>(component.get()); // Try to cast the component to ISerializable

			//	if (serializable)
			//	{
			//		sf::Packet packet = sf::Packet();
			//		serializable->Serialize(builder); // Serialize the component into the flatbuffer builder object
			//		auto data = builder.GetBufferPointer(); // Get the pointer to the serialized data
			//		auto size = builder.GetSize(); // Get the size of the serialized data
			//		packet.append(data, size); // Append the serialized data to the packet

			//		if (!isHost)
			//			SendPacket(packet, "192.168.69.11", 5000);
			//	}

			//}

			if (it->second->GetComponent<NetworkingComponent>() != nullptr)
			{
				sf::Packet packet = sf::Packet();
				it->second->Serialize(builder);
				auto data = builder.GetBufferPointer();
				auto size = builder.GetSize();
				packet.append(data, size);

				if (!isHost)
				{
					std::cout << "Sending packet to host" << std::endl;
					SendPacket(packet, NetworkManager::GetInstance().GetIp(), 5000);
				}

			}
		}

		ReceivePacket();
	}

	void NetworkingSystem::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		std::cout << "Sending packet to " << ip << ":" << port << std::endl;
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
			
			// TODO :
			// Get entity id from packet
			// Get Component type from packet


			std::vector<uint8_t> data(packet.getDataSize()); // Create a vector to store the data from the packet
			memcpy(data.data(), packet.getData(), packet.getDataSize()); // Copy the data from the packet to the vector

			auto &entities = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().GetEntities();

			for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
			{
				if (it->second->GetComponent<NetworkingComponent>() != nullptr)
				{
					it->second->Deserialize(data.data());
				}
			}
		}
	}

}
