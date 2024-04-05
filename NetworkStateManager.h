#pragma once
#include <memory>
#include <stack>

#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkStateManager
	{
		private:
			std::stack<std::shared_ptr<NetworkBaseState>> _states;
			

		public:
			NetworkStateManager();
			~NetworkStateManager();

			static NetworkStateManager& GetInstance();

			void PushState(std::shared_ptr<NetworkBaseState> state);
			void PopState();
			void ChangeState(std::shared_ptr<NetworkBaseState> state);
			NetworkBaseState& GetCurrentState();

			void Update();
	};
}
