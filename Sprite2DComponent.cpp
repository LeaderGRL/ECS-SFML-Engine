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

	void Sprite2DComponent::SetSprite(const sf::Texture& texture)
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

	std::string& Sprite2DComponent::GetTextureName()
	{
		return _textureName;
	}

	void Sprite2DComponent::PlayAnimation(const std::string& animationName, bool loop)
	{
		/*ResourceManager rs = ResourceManager::GetInstance();*/
		_animationName = animationName;
		isAnimating = true;
		shouldLoop = loop;

		const auto& animationFrames = ResourceManager::GetInstance().GetAnimation(animationName);
		if (!animationFrames.empty()) {
			//_sprite.setTexture(*animationFrames.front().texture); // Set the first frame
		}
		else {
			std::cerr << "Error: No frames for animation named " << animationName << std::endl;
		}
	}

	void Sprite2DComponent::StopAnimation(const std::string& animationName)
	{
		if (animationName == _animationName)
		{
			isAnimating = false;
			//const auto& animationFrames = ResourceManager::GetInstance().GetAnimation(animationName);
			//if (!animationFrames.empty()) {
			//	_sprite.setTexture(*animationFrames.front().texture); // Set the first frame
			//}
			//else {
			//	std::cerr << "Error: No frames for animation named " << animationName << std::endl;
			//}
		}
	}

	void Sprite2DComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}


	void Sprite2DComponent::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		auto textureName = builder.CreateString(_textureName);
		auto animationName = builder.CreateString(_animationName);

		auto sprite2DComponent = CreateSprite2DComponentSchema(builder, textureName, animationName, isAnimating, shouldLoop, currentFrameIndex, currentFrameTime, _size.x, _size.y); 
		builder.Finish(sprite2DComponent); // Serialize the root of the object to the builder
	}

	void Sprite2DComponent::Deserialize(const void* buffer)
	{
		auto sprite2DComponent = GetSprite2DComponentSchema(buffer);

		_textureName = sprite2DComponent->texture_name()->c_str();
		_animationName = sprite2DComponent->animation_name()->c_str();
		_size.x = sprite2DComponent->size_x();
		_size.y = sprite2DComponent->size_y();
		isAnimating = sprite2DComponent->is_animating();
		shouldLoop = sprite2DComponent->should_loop();
		currentFrameIndex = sprite2DComponent->current_frame_index();
		currentFrameTime = sprite2DComponent->current_frame_time();
	}
}
