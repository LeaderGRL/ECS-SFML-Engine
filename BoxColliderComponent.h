#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class BoxColliderComponent : ColliderComponent
	{
		private :
			sf::Vector2f size;

		public :
			BoxColliderComponent(sf::Vector2f size);
			~BoxColliderComponent();

			void CheckCollision(ColliderComponent* other) override;
			void Update() override;
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}
