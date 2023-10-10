#pragma once
#include <SFML/Graphics.hpp>
#include "IComponent.h"
//#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
	class Sprite2DComponent : public IComponent, public sf::Drawable
	{
		private : 
			sf::Texture texture;
			sf::Sprite sprite;
			
		protected :
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		public :
			Sprite2DComponent(std::string);
			~Sprite2DComponent();
			COMPONENT_TYPE GetType() const override;
	};
}


