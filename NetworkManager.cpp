#include "pch.h"
#include "NetworkManager.h"

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
