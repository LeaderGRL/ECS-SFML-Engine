#include "pch.h"
#include "Sprite2DComponent.h"

#include <memory>

#include "Animation2DComponentSchema_generated.h"

namespace LeaderEngine {

	Sprite2DComponent::Sprite2DComponent()
	{

	}
	
	Sprite2DComponent::Sprite2DComponent(const sf::Texture& texture)
	{
		_sprite.setTexture(texture);
	}

	Sprite2DComponent::Sprite2DComponent(const std::string& textureName)
	{
		_sprite.setTexture(ResourceManager::GetInstance().getTexture(textureName));
		_textureName = textureName;
	}

	Sprite2DComponent::~Sprite2DComponent()
	{
		
	}

	void Sprite2DComponent::Init()
	{
	}

	void Sprite2DComponent::Update(float deltaTime)
	{
		//std::cout << "texture name : " << _textureName << std::endl;
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

	std::string& Sprite2DComponent::GetTextureName() 
	{
		return _textureName;
	}

	sf::Vector2f Sprite2DComponent::GetSize()  
	{
		return _size;
	}

	COMPONENT_TYPE Sprite2DComponent::GetType() const
	{
		return COMPONENT_TYPE::SPRITE2D;
	}

	//void Sprite2DComponent::PlayAnimation(const std::string& animationName, bool loop)
	//{
	//	/*ResourceManager rs = ResourceManager::GetInstance();*/
	//	_animationName = animationName;
	//	isAnimating = true;
	//	shouldLoop = loop;

	//	const auto& animationFrames = ResourceManager::GetInstance().GetAnimation(animationName);
	//	if (!animationFrames.empty()) {
	//		//_sprite.setTexture(*animationFrames.front().texture); // Set the first frame
	//	}
	//	else {
	//		std::cerr << "Error: No frames for animation named " << animationName << std::endl;
	//	}
	//}

	//void Sprite2DComponent::StopAnimation(const std::string& animationName)
	//{
	//	if (animationName == _animationName)
	//	{
	//		isAnimating = false;
	//		//const auto& animationFrames = ResourceManager::GetInstance().GetAnimation(animationName);
	//		//if (!animationFrames.empty()) {
	//		//	_sprite.setTexture(*animationFrames.front().texture); // Set the first frame
	//		//}
	//		//else {
	//		//	std::cerr << "Error: No frames for animation named " << animationName << std::endl;
	//		//}
	//	}
	//}

	void Sprite2DComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(_sprite, states);
	}


	flatbuffers::Offset<void> Sprite2DComponent::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		std::cout << "Serializing Sprite2DComponent" << std::endl;
		const auto textureName = builder.CreateString(_textureName);

		const auto sprite2DComponent = CreateSprite2DComponentSchema(builder, textureName);
		
		//builder.Finish(sprite2DComponent); // Serialize the root of the object to the builder

		return sprite2DComponent.Union(); // Return the offset of the root of the object
		//return flatbuffers::Offset<flatbuffers::Table>(sprite2DComponent.o);
	}

	std::shared_ptr<ISerializable> Sprite2DComponent::Deserialize(const void* buffer)
	{
		if (buffer == nullptr)
		{
			std::cerr << "Error: Buffer is null." << std::endl;
			//return;
		}

		//auto verifier = flatbuffers::Verifier(static_cast<const uint8_t*>(buffer), 1024);
		//if (!VerifySprite2DComponentSchemaBuffer(verifier))
		//{
		//	std::cerr << "Error: The buffer is not a valid Sprite2DComponent schema." << std::endl;
		//	//return;
		//}

		const auto* sprite2DComponentSchema = GetSprite2DComponentSchema(buffer);

		if (sprite2DComponentSchema == nullptr)
		{
			std::cerr << "Error: Sprite2DComponent schema is null." << std::endl;
			//return;
		}

		std::cout << "Texture Name: " << sprite2DComponentSchema->texture_name()->c_str() << std::endl;

		//const std::shared_ptr<Sprite2DComponent> sprite2DComponent = std::make_shared<Sprite2DComponent>(sprite2DComponentSchema->texture_name()->c_str());
		//sprite2DComponent->SetSpriteByName(sprite2DComponentSchema->texture_name()->c_str());

		return std::make_shared<Sprite2DComponent>();
	}
}
