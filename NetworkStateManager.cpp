#include "pch.h"
#include "NetworkStateManager.h"

#include "NetworkClientState.h"
#include "NetworkHostState.h"
#include "NetworkDisconnectedState.h"

namespace LeaderEngine
{
	NetworkStateManager::NetworkStateManager()
	{
		//NetworkHostState hostState;
		PushState(std::make_shared<NetworkDisconnectedState>());
		//.push(std::make_shared<NetworkHostState>());
	}

	NetworkStateManager::~NetworkStateManager()
	{
			
	}

	NetworkStateManager& NetworkStateManager::GetInstance()
	{
		static NetworkStateManager instance;
		return instance;
	}

	void NetworkStateManager::PushState(const std::shared_ptr<NetworkBaseState>& state)
	{
		_states.push(state);
		_states.top()->Init();
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
		_states.top()->Init();
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
