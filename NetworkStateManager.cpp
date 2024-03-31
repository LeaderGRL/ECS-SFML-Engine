#include "pch.h"
#include "NetworkStateManager.h"

namespace LeaderEngine
{
	NetworkStateManager::NetworkStateManager()
	{
		
	}

	NetworkStateManager::~NetworkStateManager()
	{
			
	}

	NetworkStateManager& NetworkStateManager::GetInstance()
	{
		static NetworkStateManager instance;
		return instance;
	}

	void NetworkStateManager::PushState(std::unique_ptr<NetworkBaseState> state)
	{
		_states.push(std::move(state));
	}

	void NetworkStateManager::PopState()
	{
		_states.pop();
	}

	void NetworkStateManager::ChangeState(std::unique_ptr<NetworkBaseState> state)
	{
		if (!_states.empty())
		{
			_states.pop();
		}

		_states.push(std::move(state));
	}

	NetworkBaseState& NetworkStateManager::GetCurrentState()
	{
		return *_states.top();
	}

	void NetworkStateManager::Update()
	{
		_states.top()->Update();
	}
}
