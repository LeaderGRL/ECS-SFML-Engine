#pragma once
#include <iostream>
#include <vector>
#include "Entity.h"

using namespace std;

namespace LeaderEngine
{
	class Manager
	{
		public:
			std::vector<Entity> entities; // All entities in the game

			Entity createEntity();

		private:
	};
}


