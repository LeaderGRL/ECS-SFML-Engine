#pragma once
#include <iostream>
#include <unordered_map>
#include "Entity.h"
#include "Sprite2DComponent.h"

namespace LeaderEngine
{
	class AnimationSystem
	{
		private:
			ResourceManager rs;
		
		public:
		AnimationSystem();
		~AnimationSystem();

		void Update(const std::unordered_map<std::string, std::unique_ptr<Entity>>& entities, float deltaTime);
	};
}
