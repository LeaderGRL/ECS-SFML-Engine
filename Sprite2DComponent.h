#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawableComponent.h"
//#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
	class Sprite2DComponent : public IDrawableComponent
	{
		private : 
			sf::Texture texture;
			sf::Sprite sprite;
			
		protected :
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		public :
			Sprite2DComponent(const sf::Texture& texture);
			~Sprite2DComponent();
			void Update() override;
			COMPONENT_TYPE GetType() const override;
	};
}


