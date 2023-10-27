#include "pch.h"
#include "CollisionSystem.h"
#include "BoxColliderComponent.h"
#include "EntityManager.h"
#include <iostream>

namespace LeaderEngine
{
	CollisionSystem::CollisionSystem()
	{
		
	}

	CollisionSystem::~CollisionSystem()
	{
		
	}

	void CollisionSystem::CheckCollisions(const std::unordered_map<std::string, std::unique_ptr<Entity>>& entities)
	{
	/*	EntityManager entityManager;
		auto entities = entityManager.GetEntities();*/
		
		for (auto it1 = entities.begin(); it1 != entities.end(); ++it1)
		{
			for (auto it2 = std::next(it1); it2 != entities.end(); ++it2)
			{
			/*	auto boxCollider1 = (*it1)->GetComponent<BoxColliderComponent>();
				auto boxCollider2 = (*it2)->GetComponent<BoxColliderComponent>();*/

				if (BoxOverlap(*(it1->second), *(it2->second)))
				{
					std::cout << "Collision detected between " << it1->first << " and " << it2->first << std::endl;
				}
			}
		}
		
		/*for (int i = 0; i < entities.size(); i++)
		{
			auto& entity = entities[i]
			auto& collider = entity.GetComponent<BoxColliderComponent>();

			for (int j = i + 1; j < entities.size(); j++)
			{
				auto& otherEntity = entities[j];
				auto& otherCollider = otherEntity.GetComponent<BoxColliderComponent>();

				if (collider.IsColliding(otherCollider))
				{
					collider.OnCollision(otherCollider);
					otherCollider.OnCollision(collider);
				}
			}
		}*/
	}

	bool CollisionSystem::BoxOverlap(const Entity& a, const Entity& b)
	{
		const auto& aCollider = a.GetComponent<BoxColliderComponent>();
		const auto& bCollider = b.GetComponent<BoxColliderComponent>();

		auto aMin = a.getPosition(); // Top left
		auto aMax = aMin + aCollider->GetSize(); // Bottom right
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