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
		return std::ranges::find(_clientsInfo, ClientInfo{"", ip, port})->id;
	}

	void NetworkManager::AddClient(sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.push_back({GenerateClientId(), ip, port});
	}

	std::string NetworkManager::GenerateClientId()
	{
		const boost::uuids::uuid uuid = boost::uuids::random_generator()(); // Generate a random uuid
		return to_string(uuid);
	}

	void NetworkManager::RemoveClient(std::string id, sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.erase(std::ranges::find(_clientsInfo, ClientInfo{id, ip, port})); // C++20 way of removing an element from a vector based on a condition (in this case, the condition is that the ip and port of the client are equal to the ip and port of the client we want to remove)
		//_clientsInfo.erase(std::remove(_clientsInfo.begin(), _clientsInfo.end(), std::make_pair(ip, port)), _clientsInfo.end());
	}

	std::vector<ClientInfo> NetworkManager::GetClients()
	{
		return _clientsInfo;
	}

	bool NetworkManager::IsClientConnected(sf::IpAddress ip, unsigned short port)
	{
		return std::ranges::find(_clientsInfo, ClientInfo{GetClientId(ip, port), ip, port}) != _clientsInfo.end();
	}

	void NetworkManager::Update(float deltaTime)
	{
		NetworkStateManager::GetInstance().Update(deltaTime);
		//_networkSystem.Update();
	}
}
