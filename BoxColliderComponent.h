#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class BoxColliderComponent : public ColliderComponent, sf::Transformable
	{
		private :
			sf::Vector2f size;

		public :
			BoxColliderComponent(sf::Vector2f size);
			~BoxColliderComponent();

			//void CheckCollision(ColliderComponent* other) override;
			void Update() override;
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			//COMPONENT_TYPE GetType() const override;
	};
}
