#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>
namespace LeaderEngine
{
    class IDrawableComponent : public IComponent, public sf::Drawable
    {
        public:
            COMPONENT_TYPE GetType() const override
            {
                return COMPONENT_TYPE::DRAWABLE;
            }
		
        protected:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    };
}
