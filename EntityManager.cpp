#include "pch.h"
#include "EntityManager.h"
#include "CollisionSystem.h"

using namespace std;

namespace LeaderEngine
{	
	EntityManager& EntityManager::GetInstance()
	{
		static EntityManager instance;
		return instance;
	}

	EntityManager::EntityManager()
	{
		
	}

	EntityManager::~EntityManager()
	{
		
	}
	
	Entity* EntityManager::CreateEntity(std::string name)
	{
		std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(name);
		Entity* rawPtr = newEntity.get();
		_entities[name] = std::move(newEntity);
		//_entities.insert(std::make_pair(name, newEntity));
		return rawPtr;
	}

	Entity* EntityManager::GetEntity(const std::string& name)
	{
		const auto it = _entities.find(name);
		if (it != _entities.end())
		{
			std::cout << "Pierre, jadore ce mec !" << std::endl;
			return it->second.get();
		}
		std::cout << "Pierre, je deteste ce mec !" << std::endl;
		return nullptr;
	}

	const std::unordered_map<std::string, std::unique_ptr<Entity>>& EntityManager::GetEntities() const
	{
		return _entities;
	}

	void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		for (auto it = _entities.begin(); it != _entities.end(); it++)
		{
			it->second->draw(target, states);
		}
	}

	void EntityManager::Update(float deltaTime)
	{
		_collisionSystem.CheckCollisions(_entities);
		_animationSystem.Update(_entities, deltaTime);
		for (auto it = _entities.begin(); it != _entities.end(); it++)
		{
			it->second->Update(deltaTime);
		}
	}

	//void EntityManager::RemoveEntity(Entity& entity)
	//{
	//	// Rearranges the elements, moving the ones to be erased to the end.
	//	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
	//}

	//void EntityManager::RemoveAllEntities()
	//{
	//	_entities.clear();
	//}

	//std::unique_ptr<Entity> EntityManager::GetEntity(std::string name)
	//{
	//	return _entities[name];
	//}
	
	// First const make sure that the return value is not modifiable
	// Second const make sure that the function does not modify the class
	// & means that the function does not copy the class => Reference to the _entities vector rather than a copy of it
	/*const std::vector<Entity>& EntityManager::GetEntities() const
	{
		return _entities;
	}*/

	/*Entity* EntityManager::GetEntityById(int id)
	{
		for (auto& entity : _entities)
		{
			if (entity.GetId() == id)
			{
				return &entity;
			}
		}

		return nullptr;
	}*/
	
	//bool operator==(const Entity& lhs, const Entity& rhs)
	//{
	//	return lhs.GetId() == rhs.GetId();
	//}

}
