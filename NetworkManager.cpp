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
		_ip = ip;
	}

	void NetworkManager::SetPort(unsigned short port)
	{
		_port = port;
	}

	sf::IpAddress NetworkManager::GetIp() const
	{
		return _ip;
	}

	unsigned short NetworkManager::GetPort() const
	{
		return _port;
	}

	void NetworkManager::Update()
	{
		_networkSystem.Update();
	}
}