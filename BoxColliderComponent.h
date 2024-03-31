#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class BoxColliderComponent : public ColliderComponent, sf::Transformable
	{
		private :
			sf::Vector2f _size;

		public :
			BoxColliderComponent();
			BoxColliderComponent(sf::Vector2f size);
			~BoxColliderComponent();

			void CheckCollision(ColliderComponent* other) override;
			void Init() override;
			void Update(float deltaTime) override;
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			sf::Vector2f GetSize() const;
			void SetSize(sf::Vector2f size);
			//COMPONENT_TYPE GetType() const override;
	};
}
