#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"

namespace LeaderEngine {
	class Entity : public sf::Drawable, public sf::Transform
	{
	protected :
		int _id;
		std::vector<std::unique_ptr<IComponent>> _components;
	public:
		Entity();
		~Entity();
		int GetId();
		void SetId(int id);
		void Update(); // Update through all the components
		void Start();
		void Destroy();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Walk through all the rendable components
		
		void AddSpriteComponent2D(std::string filename);
	};
}

