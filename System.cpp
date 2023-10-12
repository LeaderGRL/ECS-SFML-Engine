#include "pch.h"
#include "System.h"

using namespace std;

namespace LeaderEngine
{
	System::System()
	{
		
	}

	System::~System()
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
	void System::AddEntity(Entity&& entity)
	{
		_entities.push_back(std::move(entity));
	}
	
	
	void System::RemoveEntity(Entity& entity)
	{
		// Rearranges the elements, moving the ones to be erased to the end.
		_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
	}

	void System::RemoveAllEntities()
	{
		_entities.clear();
	}
	
	// First const make sure that the return value is not modifiable
	// Second const make sure that the function does not modify the class
	// & means that the function does not copy the class => Reference to the _entities vector rather than a copy of it
	const std::vector<Entity>& System::GetEntities() const
	{
		return _entities;
	}
	
	bool operator==(const Entity& lhs, const Entity& rhs)
	{
		return lhs.GetId() == rhs.GetId();
	}

}
