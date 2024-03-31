#pragma once
#include "string"
#include <SFML/Network.hpp>
#include "NetworkManager.h"

namespace LeaderEngine
{
	class NetworkBaseState
	{
		public:
			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Exit() = 0;
	};
}

