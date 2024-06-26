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
			
		protected :
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			std::string _textureName;


		public :

			
			Sprite2DComponent();
			Sprite2DComponent(const sf::Texture& texture);
			Sprite2DComponent(const std::string& textureName);
			~Sprite2DComponent();

			void Init() override;
			void Update(float deltaTime) override;
			void SetSize(sf::Vector2f size);
			void SetSprite(const sf::Texture& texture);
			void SetSpriteByName(const std::string& textureName); // Textures are already loaded in ResourceManager
			sf::Sprite& GetSprite();
			std::string& GetTextureName();
			sf::Vector2f GetSize();

			COMPONENT_TYPE GetType() const override;

			flatbuffers::Offset<void> Serialize(flatbuffers::FlatBufferBuilder& builder) const override;
			std::shared_ptr<ISerializable> Deserialize(const void* buffer) override;

	};
}


#endif // SPRITE_2D_COMPONENT_H
