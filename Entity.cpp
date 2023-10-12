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
	
	void Entity::SetId(int id)
	{
		Entity::_id = id;
	}

	void Entity::Update()
	{
		for (const auto& comp : _components)
		{
			//comp.Update();
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
		//for (const auto& comp : _components)
		//{
		//	// Try to cast the component to a drawable component
		//	const IDrawableComponent* drawable = dynamic_cast<IDrawableComponent*>(comp.get());

		//	//(IComponent*)comp.get()
		//	// If successful, draw it
		//	if (drawable)
		//	{
		//		target.draw(*drawable, states);
		//	}
		//}

		for (const auto& comp : _components)
		{
			// Check if the component's type equals DRAWABLE
			if (comp->GetType() == COMPONENT_TYPE::DRAWABLE)
			{
				//std::cout << "test" << std::endl;
				//const sf::Drawable* drawable = (sf::Drawable*)comp.get();
				const IDrawableComponent* drawable = (IDrawableComponent*)comp.get();
				target.draw(*drawable, states); // Draw the drawable component if the cast was successful

			}
		}
	}

	//void Entity::AddSpriteComponent2D(std::string filename)
	//{
	//	Sprite2DComponent test(filename);
	//	_components.push_back(std::make_unique<Sprite2DComponent>(filename));
	//}

	void Entity::AddComponent(std::unique_ptr<IComponent> component)
	{
		_components.push_back(std::move(component)); // Move component into the vector
	}

	void Entity::SetPosition(float x, float y)
	{
		_position = sf::Vector2(x, y);
	}

	void Entity::SetRotation(float rotation)
	{
		_rotation = rotation;
	}

	void Entity::SetScale(float x, float y)
	{
		_scale = sf::Vector2(x, y);
	}

	void Entity::SetOrigin(float x, float y)
	{
		_origin = sf::Vector2(x, y);
	}

	void Entity::SetOrigin(sf::Vector2f origin)
	{
		_origin = origin;
	}

	void Entity::SetOriginToCenter()
	{
		_origin = sf::Vector2f(0.5f, 0.5f);
	}

	void Entity::SetOriginToTopLeft()
	{
		_origin = sf::Vector2f(0.0f, 0.0f);
	}

	void Entity::SetOriginToTopRight()
	{
		_origin = sf::Vector2f(1.0f, 0.0f);
	}

	void Entity::SetOriginToBottomLeft()
	{
		_origin = sf::Vector2f(0.0f, 1.0f);
	}

	void Entity::SetOriginToBottomRight()
	{
		_origin = sf::Vector2f(1.0f, 1.0f);
	}

	void Entity::SetOriginToTopCenter()
	{
		_origin = sf::Vector2f(0.5f, 0.0f);
	}

	void Entity::SetOriginToBottomCenter()
	{
		_origin = sf::Vector2f(0.5, 1.0f);
	}
	
	void Entity::SetOriginToLeftCenter()
	{
		_origin = sf::Vector2f(0.0f, 0.5f);
	}

	void Entity::SetOriginToRightCenter()
	{
		_origin = sf::Vector2f(1.0f, 0.5f);
	}

	int Entity::GetId()
	{
		return _id;
	}
}