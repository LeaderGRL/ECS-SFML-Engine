#include "pch.h"
#include "Animation2DComponent.h"

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

		std::cout << "name anim : " << _animationName << std::endl;
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
	}

	void Animation2DComponent::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		const auto animationName = builder.CreateString(_animationName);
		
		const auto animation2DComponent = CreateAnimation2DComponentSchema(builder, animationName, shouldLoop);
		builder.Finish(animation2DComponent);
	}

	void Animation2DComponent::Deserialize(const void* buffer)
	{
		const auto animation2DComponent = GetAnimation2DComponentSchema(buffer);
		_animationName = animation2DComponent->animation_name()->c_str();
		shouldLoop = animation2DComponent->should_loop();
	}

}
