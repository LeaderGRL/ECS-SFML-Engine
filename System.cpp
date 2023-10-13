#include "pch.h"
#include "System.h"

using namespace std;

namespace LeaderEngine
{
	EntityManager::EntityManager()
	{
		
	}

	EntityManager::~EntityManager()
	{
		
	}
	
	/*void System::Update()
	{
		for (auto& entity : m_Entities)
		{
			UpdateEntity(entity);
		}
	}*/

	// && means rvalue reference => entity is moved rather than copied => more performant for large objects
	void EntityManager::AddEntity(Entity&& entity)
	{
		_entities.push_back(std::move(entity));
	}
	
	
	void EntityManager::RemoveEntity(Entity& entity)
	{
		// Rearranges the elements, moving the ones to be erased to the end.
		_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
	}

	void EntityManager::RemoveAllEntities()
	{
		_entities.clear();
	}
	
	// First const make sure that the return value is not modifiable
	// Second const make sure that the function does not modify the class
	// & means that the function does not copy the class => Reference to the _entities vector rather than a copy of it
	const std::vector<Entity>& EntityManager::GetEntities() const
	{
		return _entities;
	}

	Entity* EntityManager::GetEntityById(int id)
	{
		for (auto& entity : _entities)
		{
			if (entity.GetId() == id)
			{
				return &entity;
			}
		}

		return nullptr;
	}
	
	bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return lhs.GetId() == rhs.GetId();
	}

}
