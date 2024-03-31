#pragma once
#include <memory>
#include <stack>

#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkStateManager
	{
		private:
			std::stack<std::unique_ptr<NetworkBaseState>> _states;
			

		public:
			NetworkStateManager();
			~NetworkStateManager();

			NetworkStateManager& GetInstance();

			void PushState(std::unique_ptr<NetworkBaseState> state);
			void PopState();
			void ChangeState(std::unique_ptr<NetworkBaseState> state);
			NetworkBaseState& GetCurrentState();

			void Update();
	};
}
