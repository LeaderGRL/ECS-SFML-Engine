#include "pch.h"
#include "NetworkStateManager.h"

#include "NetworkDisconnectedState.h"

namespace LeaderEngine
{
	NetworkStateManager::NetworkStateManager()
	{
		_states.push(std::make_shared<NetworkDisconnectedState>());
	}

	NetworkStateManager::~NetworkStateManager()
	{
			
	}

	NetworkStateManager& NetworkStateManager::GetInstance()
	{
		static NetworkStateManager instance;
		return instance;
	}

	void NetworkStateManager::PushState(std::shared_ptr<NetworkBaseState> state)
	{
		_states.push(state);
	}

	void NetworkStateManager::PopState()
	{
		_states.pop();
	}

	void NetworkStateManager::ChangeState(std::shared_ptr<NetworkBaseState> state)
	{
		if (!_states.empty())
		{
			_states.pop();
		}

		_states.push(state);
	}

	NetworkBaseState& NetworkStateManager::GetCurrentState()
	{
		return *_states.top();
	}

	std::stack<std::shared_ptr<NetworkBaseState>>& NetworkStateManager::GetStates()
	{
		return _states;
	}

	void NetworkStateManager::Update()
	{
		_states.top()->Update();
	}
}
