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
		_texture = texture;
		_sprite.setTexture(texture);
	}

	void Sprite2DComponent::SetSpriteByName(const std::string& textureName)
	{
		_textureName = textureName;
		_sprite.setTexture(ResourceManager::GetInstance().getTexture(textureName));
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

	sf::Vector2f Sprite2DComponent::GetSize()  
	{
		return _size;
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
		const auto textureName = builder.CreateString(_textureName);
		const auto animationName = builder.CreateString(_animationName);

		const auto sprite2DComponent = CreateSprite2DComponentSchema(builder, textureName, animationName, isAnimating, shouldLoop, currentFrameIndex, currentFrameTime, ResourceManager::GetInstance().GetTextureWidth(_textureName), ResourceManager::GetInstance().GetTextureHeight(_textureName)); 
		builder.Finish(sprite2DComponent); // Serialize the root of the object to the builder
	}

	void Sprite2DComponent::Deserialize(const void* buffer)
	{

		flatbuffers::Verifier verifier((const uint8_t*)buffer, 1024); // Create a verifier object to verify the buffer

		const auto* sprite2DComponent = GetSprite2DComponentSchema(buffer);

		//_textureName = sprite2DComponent->texture_name()->c_str();
		//_animationName = sprite2DComponent->animation_name()->c_str();
		//isAnimating = sprite2DComponent->is_animating();
		//shouldLoop = sprite2DComponent->should_loop();
		//currentFrameIndex = sprite2DComponent->current_frame_index();
		//currentFrameTime = sprite2DComponent->current_frame_time();
		//_size.x = sprite2DComponent->size_x();
		//_size.y = sprite2DComponent->size_y();

		//std::cout << "Deserialized Sprite2DComponent" << std::endl;
		std::cout << "Texture Name: " << sprite2DComponent->texture_name()->c_str() << std::endl;
		std::cout << "Animation Name: " << sprite2DComponent->animation_name()->c_str()<< std::endl;
		std::cout << "Size: " << sprite2DComponent->size_x() << ", " << sprite2DComponent->size_y() << std::endl;
		std::cout << "Is Animating: " << sprite2DComponent->is_animating() << std::endl;
		std::cout << "Should Loop: " << sprite2DComponent->should_loop() << std::endl;

	}
}
