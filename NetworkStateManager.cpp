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
		//PushState(std::make_shared<NetworkDisconnectedState>());
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
		//std::lock_guard<std::mutex> lock(_mutex);

		if (state) {
			std::cout << "Pushing state: " << typeid(*state).name() << std::endl;
			_states.push(state);
			_states.top()->Init();
		}
		else {
			std::cerr << "Error: Attempted to push a null state." << std::endl;
		}
	}

	void NetworkStateManager::PopState()
	{
		//std::lock_guard<std::mutex> lock(_mutex);

		if (!_states.empty()) {
			_states.top()->Exit();
			_states.pop();
			std::cout << "Popped state" << std::endl;
		}
		else {
			std::cerr << "Error: Attempted to pop from an empty state stack." << std::endl;
		}
	}

	void NetworkStateManager::ChangeState(std::shared_ptr<NetworkBaseState> state)
	{
		//std::lock_guard<std::mutex> lock(_mutex);

		if (!_states.empty()) {
			_states.top()->Exit();
			_states.pop();
		}
		if (state) {
			_states.push(state);
			_states.top()->Init();
			std::cout << "Changed state to: " << typeid(*state).name() << std::endl;
		}
		else {
			std::cerr << "Error: Attempted to change to a null state." << std::endl;
		}

		/*if (!_states.empty())
		{
			_states.pop();
		}

		_states.push(state);
		_states.top()->Init();

		std::cout << "Changing state" << std::endl;*/
	}

	NetworkBaseState& NetworkStateManager::GetCurrentState()
	{
		//std::lock_guard<std::mutex> lock(_mutex);

		if (_states.empty())
		{
			throw std::runtime_error("No states in the stack");
		}

		return *_states.top();
	}

	std::stack<std::shared_ptr<NetworkBaseState>>& NetworkStateManager::GetStates()
	{
		//std::lock_guard<std::mutex> lock(_mutex);

		if (_states.empty())
		{
			throw std::runtime_error("No states in the stack");
		}

		return _states;
	}

	void NetworkStateManager::Update(float deltaTime)
	{
		//std::lock_guard<std::mutex> lock(_mutex);

		if (_states.empty())
		{
			return;
		}

		_states.top()->Update(deltaTime);
	}
}
