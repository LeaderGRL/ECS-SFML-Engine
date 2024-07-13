#include "pch.h"
#include "NetworkManager.h"

#include "NetworkPacketType.h"
#include "NetworkStateManager.h"

namespace LeaderEngine
{
	NetworkManager::NetworkManager()
	{

	}

	NetworkManager::~NetworkManager()
	{
	}

	NetworkManager& NetworkManager::GetInstance()
	{
		static NetworkManager instance;
		return instance;
	}

	void NetworkManager::SetIp(sf::IpAddress ip)
	{
		_hostIp = ip;
	}

	void NetworkManager::SetPort(unsigned short port)
	{
		_port = port;
	}

	sf::IpAddress NetworkManager::GetIp()
	{
		return _hostIp;
	}

	unsigned short NetworkManager::GetPort()
	{
		return _port;
	}

	std::string NetworkManager::GetClientId(sf::IpAddress ip, unsigned short port)
	{
		auto key = GenerateKey(ip, port);
		auto it = std::find_if(_clientsInfo.begin(), _clientsInfo.end(), [key](const std::pair<std::string, ClientInfo>& pair) // C++20 way of finding an element in a vector based on a condition (in this case, the condition is that the key of the pair is equal to the key we are looking for)
		{
			return pair.first == key;
		});

		if (it != _clientsInfo.end())
		{
			return it->second.id;
		}
		else
		{
			return "";
		}
	}

	sf::UdpSocket& NetworkManager::GetSocket()
	{
		return _socket;
	}

	std::string NetworkManager::GetUUID()
	{
		return _UUID;
	}

	std::string NetworkManager::GetLastNElementsOfUUID(int n)
	{
		if (n > _UUID.size()) // WARNING : Not the good way to manage this case
		{
			return _UUID;
		}
		return _UUID.substr(_UUID.size() - n);
	}

	void NetworkManager::SetUUID(std::string uuid)
	{
		_UUID = uuid;
	}

	void NetworkManager::AddClient(sf::IpAddress ip, unsigned short port)
	{
		auto key = GenerateKey(ip, port);
		if (_clientsInfo.find(key) == _clientsInfo.end())
		{
			_clientsInfo[key] = ClientInfo{GenerateClientId(), ip, port};
		}
		else
		{
			std::cout << "Client already exists" << std::endl;
		}
	}

	std::string NetworkManager::GenerateClientId()
	{
		const boost::uuids::uuid uuid = boost::uuids::random_generator()(); // Generate a random uuid
		std::cout << "Generated UUID : " << to_string(uuid) << std::endl;
		return to_string(uuid);
	}

	void NetworkManager::HandleIncomingPackets(sf::Packet& packet, const sf::IpAddress& sender, unsigned short senderPort)
	{
		sf::Int32 packetType;
		//packet >> packetType;

		if (!(packet >> packetType))
		{
			std::cerr << "Error: Invalid packet type or failed to read packet type." << std::endl;
			return;
		}

		std::cout << "Received packet of type: " << packetType << std::endl;

		switch (packetType)
		{
			case static_cast<sf::Int32>(NetworkPacketType::ENTITIES):
				std::cout << "Received entities packet" << std::endl;
				HandleEntitiesPacket(packet, sender, senderPort);
			break;

			default:
				std::cerr << "Error: Invalid packet type." << std::endl;
			break;
		}
	}

	void NetworkManager::HandleEntitiesPacket(sf::Packet& packet, const sf::IpAddress& sender, unsigned short senderPort)
	{
		flatbuffers::FlatBufferBuilder builder;

		std::string entityId;
		//packet >> entityId;

		if (!(packet >> entityId) || entityId.empty())
		{
			std::cerr << "Error: Invalid or empty entity ID." << std::endl;
			return;
		}

		auto& entityManager = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager();
		auto entity = entityManager.GetEntity(entityId);

		if (!entity)
		{
			std::cerr << "Error: Received unknown entity: " << entityId << std::endl;
			return;
		}

		auto* networkComponent = entity->GetComponent<NetworkingComponent>();
		if (!networkComponent)
		{
			std::cerr << "Error: Entity " << entityId << " does not have a NetworkingComponent." << std::endl;
			return;
		}

		const char* data = static_cast<const char*>(packet.getData()) + packet.getReadPosition();
		std::size_t dataSize = packet.getDataSize() - packet.getReadPosition();

		if (!entity->Deserialize(data))
		{
			std::cerr << "Error: Failed to deserialize entity " << entityId << std::endl;
			return;
		}

		networkComponent->SetDirty(false);
	}

	void NetworkManager::BroadcastEntitiesPacket()
	{

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

			auto packet = CreateEntityPacket(*it->second);

			for (auto& client : _clientsInfo)
			{
				// -- TEMPORARY -- //
				if (client.second.ip == _hostIp && client.second.port == _port) // Avoid host sending data to itself
				{
					continue;
				}
				SendPacket(packet, client.second.ip, client.second.port);
			}

			networkComponent->SetDirty(false);
		}
	}

	sf::Packet NetworkManager::CreateEntityPacket(const Entity& entity)
	{
		flatbuffers::FlatBufferBuilder builder;
		sf::Packet packet = sf::Packet();

		sf::Int32 dataType = static_cast<sf::Int32>(NetworkPacketType::ENTITIES);
		packet << dataType;

		packet << entity.GetId();
		entity.Serialize(builder);
		const auto data = builder.GetBufferPointer();
		const auto size = builder.GetSize();
		packet.append(data, size);

		return packet;
	}

	void NetworkManager::SendPacket(sf::Packet& packet, const sf::IpAddress ip, const unsigned short port)
	{
		std::cout << "Sending packet to " << ip.toString() << " : " << port << std::endl;
		if (_socket.send(packet, ip, port) != sf::Socket::Done)
		{
			std::cerr << "Error: Failed to send packet." << std::endl;
		}
	}

	void NetworkManager::SendEntityPacket(const Entity& entity, const sf::IpAddress ip, const unsigned short port)
	{
		sf::Packet packet = CreateEntityPacket(entity);
		SendPacket(packet, ip, port);
	}

	void NetworkManager::RemoveClient(std::string id, sf::IpAddress ip, unsigned short port)
	{
		auto key = GenerateKey(ip, port);
		_clientsInfo.erase(key);
	}

	std::unordered_map<std::string, ClientInfo> NetworkManager::GetClients()
	{
		return _clientsInfo;
	}

	bool NetworkManager::IsClientConnected(sf::IpAddress ip, unsigned short port)
	{
		auto key = GenerateKey(ip, port);
		return _clientsInfo.find(key) != _clientsInfo.end(); // Check if the client is connected by checking if the key exists in the unordered_map
	}

	void NetworkManager::Update(float deltaTime)
	{
		NetworkStateManager::GetInstance().Update(deltaTime);
		//_networkSystem.Update();
	}
}
