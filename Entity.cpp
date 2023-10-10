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
	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const auto& comp : _components)
		{
			// Try to cast the component to a drawable component
			const IDrawableComponent* drawable = dynamic_cast<IDrawableComponent*>(comp.get());

			// If successful, draw it
			if (drawable)
			{
				target.draw(*drawable, states);
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