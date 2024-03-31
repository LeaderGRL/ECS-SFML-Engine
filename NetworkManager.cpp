#include "pch.h"
#include "NetworkManager.h"

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

	sf::IpAddress NetworkManager::GetIp() const
	{
		return _hostIp;
	}

	unsigned short NetworkManager::GetPort() const
	{
		return _port;
	}

	void NetworkManager::AddClient(sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.push_back({ip, port});
	}

	void NetworkManager::RemoveClient(sf::IpAddress ip, unsigned short port)
	{
		_clientsInfo.erase(std::remove(_clientsInfo.begin(), _clientsInfo.end(), std::make_pair(ip, port)), _clientsInfo.end());
	}

	std::vector<ClientInfo> NetworkManager::GetClients() const
	{
		return _clientsInfo;
	}

	bool NetworkManager::IsClientConnected(sf::IpAddress ip, unsigned short port) const
	{
		return std::find(_clientsInfo.begin(), _clientsInfo.end(), std::make_pair(ip, port)) != _clientsInfo.end();
	}

	void NetworkManager::Update()
	{
		_networkSystem.Update();
	}
}