#include "pch.h"
#include "NetworkingSystem.h"

#include "EntityManager.h"

namespace LeaderEngine
{
	NetworkingSystem::NetworkingSystem()
	{
		socket.bind(5000);
		socket.setBlocking(false);

		if ( sf::IpAddress::getLocalAddress().toString() == "192.168.69.11" )
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
		auto &entities = EntityManager::GetInstance().GetEntities(); // Reference to the entities map in the entity manager

		for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
		{
			for (auto& component : it->second->GetComponents()) // Iterate through the components of the entity
			{
				auto serializable = dynamic_cast<ISerializable*>(component.get()); // Try to cast the component to ISerializable

				if (serializable)
				{
					sf::Packet packet = sf::Packet();
					serializable->Serialize(builder); // Serialize the component into the flatbuffer builder object
					auto data = builder.GetBufferPointer(); // Get the pointer to the serialized data
					auto size = builder.GetSize(); // Get the size of the serialized data
					packet.append(data, size); // Append the serialized data to the packet

					if (!isHost)
						SendPacket(packet, "192.168.69.11", 5000);
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

			auto &entities = EntityManager::GetInstance().GetEntities();

			for (auto it = entities.begin(); it != entities.end(); ++it) // Iterate through the entities 
			{
				for (auto& component : it->second->GetComponents()) // Iterate through the components of the entity
				{
					auto serializable = dynamic_cast<ISerializable*>(component.get()); // Try to cast the component to ISerializable

					if (serializable)
					{
						serializable->Deserialize(data.data()); // Deserialize the data into the component
					}
				}
			}
		}
	}

}
