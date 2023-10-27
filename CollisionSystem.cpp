#include "pch.h"
#include "CollisionSystem.h"
#include "BoxColliderComponent.h"

namespace LeaderEngine
{
	CollisionSystem::CollisionSystem()
	{
		
	}

	CollisionSystem::~CollisionSystem()
	{
		
	}

	void CollisionSystem::CheckCollisions(const std::vector<Entity>& entities)
	{
		/*for (auto& entity : entities)
		{
			if (entity.HasComponent<ColliderComponent>())
			{
				auto& collider = entity.GetComponent<ColliderComponent>();
				collider.Colliding = false;
				for (auto& otherEntity : entities)
				{
					if (otherEntity.HasComponent<ColliderComponent>())
					{
						auto& otherCollider = otherEntity.GetComponent<ColliderComponent>();
						if (collider.CollidesWith(otherCollider))
						{
							collider.Colliding = true;
							collider.CollidingWith = otherEntity;
							break;
						}
					}
				}
			}
		}*/
	}

	bool CollisionSystem::BoxOverlap(const Entity& a, const Entity& b)
	{
		//auto& aTransform = a.getTransform()
		const auto& aCollider = a.GetComponent<BoxColliderComponent>();
		//auto& bTransform = b.GetComponent<TransformComponent>();
		const auto& bCollider = b.GetComponent<BoxColliderComponent>();

		auto aMin = a.getPosition();
		auto aMax = aMin + aCollider->GetSize();
		auto bMin =	b.getPosition();
		auto bMax = bMin + bCollider->GetSize();

		return (aMin.x < bMax.x && aMax.x > bMin.x) &&
			(aMin.y < bMax.y && aMax.y > bMin.y);
	}

	bool CollisionSystem::PreciseCollision(const Entity& a, const Entity& b)
	{
		return true;
	}

	void CollisionSystem::ResolveCollision(Entity& a, Entity& b)
	{
		
	}
}