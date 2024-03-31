#pragma once
#include "NetworkBaseState.h"

namespace LeaderEngine
{
	class NetworkDisconnectedState : public NetworkBaseState
	{
		public:
			void Init() override;
			void Update() override;
			void Exit() override;
	};
}

