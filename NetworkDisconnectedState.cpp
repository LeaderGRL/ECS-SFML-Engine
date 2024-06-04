#include "pch.h"
#include "NetworkDisconnectedState.h"

namespace LeaderEngine
{
	void NetworkDisconnectedState::Init()
	{
		std::cout << "Network Disconnected State Initialized" << std::endl;
	}

	void NetworkDisconnectedState::Update(float deltaTime)
	{
		std::cout << "Update Network Disconnected State" << std::endl;
	}

	void NetworkDisconnectedState::Exit()
	{
		std::cout << "Exiting Network Disconnected State" << std::endl;
	}
}