#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"
#include <iostream>

namespace LeaderEngine {
	Entity::Entity()
	{
		Entity::_id = 0;
	}

	Entity::~Entity()
	{
		
	}

	Entity::Entity(std::string name)
	{
		
	}
	
	void Entity::SetId(int id)
	{
		Entity::_id = id;
	}

	void Entity::Update() const // WARNING : Check if the "const" cannot be a problem in the future
	{
		for (const auto& comp : _components)
		{
			comp.get()->Update(); // Call all component Update()
		}
	}

	void Entity::Start()
	{
		
	}

	void Entity::Destroy()
	{
		
	}

	// Draw all drawable components of the entity
	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.combine(getTransform()); // Apply the entity transform to the drawable components
		for (const auto& comp : _components) 
		{
			if (comp->GetType() == COMPONENT_TYPE::DRAWABLE) // Check if the component's type equals DRAWABLE
			{
				const IDrawableComponent* drawable = (IDrawableComponent*)comp.get();
				target.draw(*drawable, states); // Draw the drawable component if the cast was successful
			}
		}
	}

	//void Entity::AddComponent(std::unique_ptr<IComponent> component)
	//{
	//	_components.push_back(std::move(component)); // Move component into the vector
	//}

	int Entity::GetId() const
	{
		return _id;
	}

	
}