#include "pch.h"
#include "Animation2DComponent.h"

#include <memory>

namespace  LeaderEngine
{
	Animation2DComponent::Animation2DComponent()
	{
	}

	Animation2DComponent::Animation2DComponent(const std::string& animationName, bool loop, bool animating)
	{
		_animationName = animationName;
		shouldLoop = loop;
		isAnimating = animating;
		_textureName = ResourceManager::GetInstance().GetTextureNameFromAnimationName(_animationName);
	}

	Animation2DComponent::~Animation2DComponent()
	{
	}

	void Animation2DComponent::PlayAnimation(bool loop)
	{
		isAnimating = true;
		shouldLoop = loop;
	}

	void Animation2DComponent::StopAnimation()
	{
		isAnimating = false;
		shouldLoop = false;
	}

	std::string& Animation2DComponent::GetAnimationName()
	{
		return _animationName;
	}

	void Animation2DComponent::SetAnimationName(const std::string& animationName)
	{
		_animationName = animationName;
		_textureName = ResourceManager::GetInstance().GetTextureNameFromAnimationName(_animationName);
	}

	flatbuffers::Offset<void> Animation2DComponent::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		std::cout << "Serializing Animation2DComponent" << std::endl;
		const auto animationName = builder.CreateString(_animationName);
		
		const auto animation2DComponent = CreateAnimation2DComponentSchema(builder, animationName, shouldLoop, isAnimating);
		//builder.Finish(animation2DComponent);

		return  animation2DComponent.Union();
	}

	std::shared_ptr<ISerializable> Animation2DComponent::Deserialize(const void* buffer)
	{
		const auto animation2DComponent = GetAnimation2DComponentSchema(buffer);
		_animationName = animation2DComponent->animation_name()->c_str();
		shouldLoop = animation2DComponent->should_loop();
		isAnimating = animation2DComponent->is_animating();
		return std::make_shared<Animation2DComponent>();
	}

}
