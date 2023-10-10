#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"

namespace LeaderEngine {
	Entity::Entity()
	{
		Entity::_id = 0;
	}

	Entity::~Entity()
	{
		
	}
	
	void Entity::SetId(int id)
	{
		Entity::_id = id;
	}

	void Entity::Update()
	{
		
	}

	void Entity::Start()
	{
		
	}

	void Entity::Destroy()
	{
		
	}

	// Draw all drawable components of the entity
	void Entity::Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& comp : _components)
		{
			// Check if the component's type equals DRAWABLE
			if (comp->GetType() == COMPONENT_TYPE::DRAWABLE)
			{
				const sf::Drawable* drawable = static_cast<const sf::Drawable*>(comp.get()); // Static Cast didn't work beacause of C++
				target.draw(*drawable, states); // Draw the drawable component if the cast was successful

			}
		}
	}

	void Entity::AddSpriteComponent2D(std::string filename)
	{
		Sprite2DComponent test(filename);
		_components.push_back(std::make_unique<Sprite2DComponent>(filename));
	}

	int Entity::GetId()
	{
		return _id;
	}
}