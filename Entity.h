#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"

namespace LeaderEngine {
	class Entity : public sf::Drawable, public sf::Transformable
	{
	protected :
		int _id;
		float _x;
		float _y;
		float _z;
		float _width;
		float _height;
		float _rotation;
		sf::Vector2f _position;
		sf::Vector2f _scale;
		sf::Vector2f _origin;
		std::vector<std::unique_ptr<IComponent>> _components;
	public:
		Entity();
		Entity(const Entity&) = delete; // delete copy constructor
		Entity& operator=(const Entity&) = delete; // delete copy assignment
		Entity(Entity&&) = default; // use default move constructor
		Entity& operator=(Entity&&) = default; // use default move assignment
		~Entity();
		int GetId() const;
		void SetId(int id);
		void Update() const; // Update through all the components
		void Start();
		void Destroy();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Walk through all the rendable components
		void AddComponent(std::unique_ptr<IComponent> component);

	};
}