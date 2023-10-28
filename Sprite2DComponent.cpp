#include "pch.h"
#include "Sprite2DComponent.h"

namespace LeaderEngine {

	Sprite2DComponent::Sprite2DComponent()
	{
		
	}
	
	Sprite2DComponent::Sprite2DComponent(const sf::Texture& texture)
	{
		_sprite.setTexture(texture);
	}

	Sprite2DComponent::~Sprite2DComponent()
	{
		
	}

	void Sprite2DComponent::Update(float deltaTime)
	{
		
	}

	void Sprite2DComponent::SetSize(sf::Vector2f size)
	{
		 _sprite.setScale(size.x / _sprite.getLocalBounds().width, size.y / _sprite.getLocalBounds().height);
	}

	std::string& Sprite2DComponent::GetAnimationName()
	{
		return _animationName;
	}

	void Sprite2DComponent::PlayAnimation(const std::string& animationName, bool loop)
	{
		ResourceManager rs;
		_animationName = animationName;
		isAnimating = true;
		shouldLoop = loop;
		_sprite.setTexture(*(rs.GetAnimation(animationName)[0].texture));
	}

	void Sprite2DComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}

	//COMPONENT_TYPE Sprite2DComponent::GetType() const
	//{
	//	return COMPONENT_TYPE::DRAWABLE;
	//}
}
