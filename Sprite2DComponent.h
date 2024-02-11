#pragma once

#ifndef SPRITE_2D_COMPONENT_H // include guard for Sprite2DComponent.h to avoid multiple definitions
#define SPRITE_2D_COMPONENT_H

#include <SFML/Graphics.hpp>
#include "IDrawableComponent.h"
#include "ISerializable.h"
#include "ResourceManager.h"
#include "Sprite2DComponentSchema_generated.h"
//#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
	class Sprite2DComponent : public IDrawableComponent, public ISerializable
	{
		private : 
			sf::Texture _texture;
			sf::Sprite _sprite;
			sf::Vector2f _size;
			std::string _animationName;
			std::string _textureName;
			
		protected :
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		public :
			bool isAnimating = false;
			bool shouldLoop = true;
			int currentFrameIndex = 0;
			float currentFrameTime = 0;
			
			Sprite2DComponent();
			Sprite2DComponent(const sf::Texture& texture);
			~Sprite2DComponent();
			void PlayAnimation(const std::string& animationName, bool loop = true);
			void StopAnimation(const std::string& animationName);
			void Update(float deltaTime) override;
			void SetSize(sf::Vector2f size);
			void SetSprite(const sf::Texture& texture);
			sf::Sprite& GetSprite();
			std::string& GetAnimationName();
			std::string& GetTextureName();

			void Serialize(flatbuffers::FlatBufferBuilder& builder) const override;
			void Deserialize(const void* buffer) override;

	};
}


#endif // SPRITE_2D_COMPONENT_H
