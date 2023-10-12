#include "pch.h"
#include "Sprite2DComponent.h"

namespace LeaderEngine {

	Sprite2DComponent::Sprite2DComponent(std::string filepath)
	{
		texture.loadFromFile(filepath);
		sprite.setTexture(texture);
	}

	Sprite2DComponent::~Sprite2DComponent()
	{
		
	}

	void Sprite2DComponent::Update()
	{
		//sprite.setPosition(transform.position);
		//sprite.setRotation(transform.rotation);
		//sprite.setScale(transform.scale);
	}

	void Sprite2DComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

	COMPONENT_TYPE Sprite2DComponent::GetType() const
	{
		return COMPONENT_TYPE::DRAWABLE;
	}
}