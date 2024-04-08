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

	void NetworkManager::AddClient(sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.push_back({ip, port});
	}

	void NetworkManager::RemoveClient(sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.erase(std::ranges::find(_clientsInfo, ClientInfo{ip, port})); // C++20 way of removing an element from a vector based on a condition (in this case, the condition is that the ip and port of the client are equal to the ip and port of the client we want to remove)
		//_clientsInfo.erase(std::remove(_clientsInfo.begin(), _clientsInfo.end(), std::make_pair(ip, port)), _clientsInfo.end());
	}

	std::vector<ClientInfo> NetworkManager::GetClients()
	{
		return _clientsInfo;
	}

	bool NetworkManager::IsClientConnected(sf::IpAddress ip, unsigned short port)
	{
		return std::ranges::find(_clientsInfo, ClientInfo{ip, port}) != _clientsInfo.end();
	}

	void NetworkManager::Update()
	{
		NetworkStateManager::GetInstance().Update();
	}
}
