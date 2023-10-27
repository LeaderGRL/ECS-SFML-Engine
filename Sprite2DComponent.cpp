#include "pch.h"
#include "Sprite2DComponent.h"

namespace LeaderEngine {

	Sprite2DComponent::Sprite2DComponent(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
	}

	Sprite2DComponent::~Sprite2DComponent()
	{
		
	}

	void Sprite2DComponent::Update(float deltaTime)
	{
		/*sprite.setPosition();
		sprite.setRotation(transform.rotation);
		sprite.setScale(transform.scale);*/
	}

	void Sprite2DComponent::SetSize(sf::Vector2f size)
	{
		 sprite.setScale(size.x / sprite.getLocalBounds().width, size.y / sprite.getLocalBounds().height);
	}

	void Sprite2DComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

	//COMPONENT_TYPE Sprite2DComponent::GetType() const
	//{
	//	return COMPONENT_TYPE::DRAWABLE;
	//}
}
