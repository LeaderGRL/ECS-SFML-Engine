#pragma once
#include "Entity.h"

namespace LeaderEngine
{
	class CollisionSystem
	{
		public:
			CollisionSystem();
			~CollisionSystem();
			void CheckCollisions(const std::vector<Entity>& entities);
			bool BoxOverlap(const Entity& a, const Entity& b);


		private:
			/*bool SphereOverlap(const Entity& entity1, const Entity& entity2);
			bool BoxSphereOverlap(const Entity& entity1, const Entity& entity2);
			bool BoxBoxOverlap(const Entity& entity1, const Entity& entity2);
			bool SphereSphereOverlap(const Entity& entity1, const Entity& entity2);
			bool SphereBoxOverlap(const Entity& entity1, const Entity& entity2);*/

			bool PreciseCollision(const Entity& a, const Entity& b);
			void ResolveCollision(Entity& a, Entity& b);
			
	};
}
