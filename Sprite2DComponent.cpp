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

	void Sprite2DComponent::Init()
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

	std::string& Sprite2DComponent::GetTextureName() 
	{
		return _textureName;
	}

	sf::Vector2f Sprite2DComponent::GetSize()  
	{
		return _size;
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
		const auto textureName = builder.CreateString(_textureName);

		const auto sprite2DComponent = CreateSprite2DComponentSchema(builder, textureName);
		builder.Finish(sprite2DComponent); // Serialize the root of the object to the builder

		return sprite2DComponent.Union(); // Return the offset of the root of the object
		//return flatbuffers::Offset<flatbuffers::Table>(sprite2DComponent.o);
	}

	void Sprite2DComponent::Deserialize(const void* buffer)
	{
		const auto* sprite2DComponentSchema = GetSprite2DComponentSchema(buffer);

		std::cout << "Texture Name: " << sprite2DComponentSchema->texture_name()->c_str() << std::endl;


	}
}
