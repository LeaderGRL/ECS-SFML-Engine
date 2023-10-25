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
		float _width;
		float _height;
		float _rotation;
		sf::Vector2f _position;
		sf::Vector2f _scale;
		sf::Vector2f _origin;
		std::vector<std::unique_ptr<IComponent>> _components;
	public:
		Entity();
		~Entity();
		Entity(std::string name);
		Entity(const Entity&) = delete; // delete copy constructor
		Entity& operator=(const Entity&) = delete; // delete copy assignment
		Entity(Entity&&) = default; // use default move constructor
		Entity& operator=(Entity&&) = default; // use default move assignment
		
		int GetId() const;
		void SetId(int id);
		void Update() const; // Update through all the components
		void Start();
		void Destroy();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Walk through all the rendable components
		
		template<typename T, typename ...Args> 
		void AddComponent(Args&&... args) // r value reference on n arguments
		{
			static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from IComponent"); // Check if T inherit from IComponent
			_components.push_back(std::make_unique<T>(std::forward<Args>(args)...)); // forwards the arguments args to the constructor of T with their original value
		}
		
		template<typename T>
		T* GetComponent()
		{
			for (const auto& comp : _components)
			{
				if (dynamic_cast<T*>(comp.get()))
					return static_cast<T*>(comp.get());
			}
			return nullptr;
		}

	};
}