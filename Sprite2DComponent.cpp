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

	void Sprite2DComponent::SetSprite(sf::Texture& texture)
	{
		_sprite.setTexture(texture);
	}

	sf::Sprite& Sprite2DComponent::GetSprite()
	{
		return _sprite;
	}

	std::string& Sprite2DComponent::GetAnimationName()
	{
		return _animationName;
	}

	void Sprite2DComponent::PlayAnimation(const std::string& animationName, bool loop)
	{
		/*ResourceManager rs = ResourceManager::GetInstance();*/
		_animationName = animationName;
		isAnimating = true;
		shouldLoop = loop;
		
		const auto& animationFrames = ResourceManager::GetInstance().GetAnimation(animationName);
		if (!animationFrames.empty()) {
			_sprite.setTexture(*animationFrames.front().texture);
		}
		else {
			std::cerr << "Error: No frames for animation named " << animationName << std::endl;
		}
	}

	void Sprite2DComponent::StopAnimation(const std::string& animationName)
	{
		if (animationName == _animationName)
			isAnimating = false;
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
