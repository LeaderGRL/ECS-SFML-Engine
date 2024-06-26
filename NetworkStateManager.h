#pragma once
#include <memory>
#include <mutex>
#include <stack>

#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkStateManager
	{
		private:
			std::stack<std::shared_ptr<NetworkBaseState>> _states;
			std::mutex _mutex;


		public:
			NetworkStateManager();
			~NetworkStateManager();

			static NetworkStateManager& GetInstance();

			void PushState(const std::shared_ptr<NetworkBaseState>& state);
			void PopState();
			void ChangeState(std::shared_ptr<NetworkBaseState> state);
			NetworkBaseState& GetCurrentState();
			std::stack<std::shared_ptr<NetworkBaseState>>& GetStates();

			void Update(float deltaTime);
	};
}
