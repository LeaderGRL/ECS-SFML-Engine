#include "pch.h"
#include "NetworkingSystem.h"

#include "EntityManager.h"

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
		flatbuffers::FlatBufferBuilder builder;
		auto &entities = EntityManager::GetInstance().GetEntities();

		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			for (auto& component : it->second->GetComponents())
			{
				auto serializable = dynamic_cast<ISerializable*>(component.get());

				if (serializable)
				{
					sf::Packet packet = sf::Packet();
					serializable->Serialize(builder); // Serialize the component into the flatbuffer builder object
					auto data = builder.GetBufferPointer(); // Get the pointer to the serialized data
					auto size = builder.GetSize(); // Get the size of the serialized data
					packet.append(data, size); // Append the serialized data to the packet

					SendPacket(packet, "localhost", 5000);
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

		}
	}

}
