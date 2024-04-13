#pragma once
#include "string"
#include <SFML/Network.hpp>
#include "SceneManager.h"
#include "NetworkingComponent.h"

namespace LeaderEngine
{
	class NetworkBaseState
	{
		public:
			virtual ~NetworkBaseState() = default;

			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Exit() = 0;
	};
}

