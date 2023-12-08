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
			ResourceManager& rs = ResourceManager::GetInstance();
			//ResourceManager& rs = ResourceManager::GetInstance();
		
		public:
			AnimationSystem();
			~AnimationSystem();

			void Update(const std::unordered_map<std::string, std::unique_ptr<Entity>>& entities, float deltaTime);
			void UpdateEntity(Entity* entity, float deltaTime);
			void UpdateAnimation(Entity* entity, float deltaTime);
	};
}
