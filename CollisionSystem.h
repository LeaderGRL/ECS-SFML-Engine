#pragma once
#include "Entity.h"
#include <unordered_map>

namespace LeaderEngine
{
	class CollisionSystem
	{
		public:
			CollisionSystem();
			~CollisionSystem();
			void CheckCollisions(const std::unordered_map<std::string, std::shared_ptr<Entity>>& entities);


		private:
			/*bool SphereOverlap(const Entity& entity1, const Entity& entity2);
			bool BoxSphereOverlap(const Entity& entity1, const Entity& entity2);
			bool BoxBoxOverlap(const Entity& entity1, const Entity& entity2);
			bool SphereSphereOverlap(const Entity& entity1, const Entity& entity2);
			bool SphereBoxOverlap(const Entity& entity1, const Entity& entity2);*/
			
			bool BoxOverlap(const Entity& a, const Entity& b);
			bool PreciseCollision(const Entity& a, const Entity& b);
			void ResolveCollision(Entity& a, Entity& b);
			
	};
}
