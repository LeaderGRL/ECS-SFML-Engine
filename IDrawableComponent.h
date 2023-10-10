#pragma once
#include "IComponent.h"
#include <SFML/Graphics.hpp>
namespace LeaderEngine
{
    class IDrawableComponent : public IComponent, public sf::Drawable
    {
        protected:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    };
}
