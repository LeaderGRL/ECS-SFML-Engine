#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"

namespace LeaderEngine {
	class Entity : public sf::Drawable, public sf::Transform
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
		~Entity();
		int GetId();
		void SetId(int id);
		void Update(); // Update through all the components
		void Start();
		void Destroy();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Walk through all the rendable components
		//void AddSpriteComponent2D(std::string filename);
		void AddComponent(std::unique_ptr<IComponent> component);
		void SetPosition(float x, float y);
		void SetRotation(float rotation);
		void SetScale(float width, float height);
		void SetOrigin(float x, float y);
		void SetOrigin(sf::Vector2f origin);
		void SetOriginToCenter();
		void SetOriginToTopLeft();
		void SetOriginToTopRight();
		void SetOriginToBottomLeft();
		void SetOriginToBottomRight();
		void SetOriginToTopCenter();
		void SetOriginToBottomCenter();
		void SetOriginToLeftCenter();
		void SetOriginToRightCenter();
	};
}