#include "pch.h"
#include "AnimationSystem.h"

#include "Animation2DComponent.h"

namespace LeaderEngine
{
	AnimationSystem::AnimationSystem()
	{
		
	}

	AnimationSystem::~AnimationSystem()
	{
		
	}

	void AnimationSystem::Update(const std::unordered_map<std::string, std::unique_ptr<Entity>>& entities, float deltaTime)
	{
		for (const auto& pair : entities)
		{
			UpdateEntity(pair.second.get(), deltaTime);
		}
	}

	void AnimationSystem::UpdateEntity(Entity* entity, float deltaTime)
	{
		UpdateAnimation(entity, deltaTime);

		for (const auto& pair : entity->GetChildren())
		{
			UpdateEntity(pair.second.get(), deltaTime); // recursive call
		}
	}

	void AnimationSystem::UpdateAnimation(Entity* entity, float deltaTime)
	{
		Animation2DComponent* animationComp = entity->GetComponent<Animation2DComponent>();

		if (!animationComp)
			return;

		//if (!animationComp->isAnimating)
		//{
		//	//const sf::Texture* texture = rs.GetAnimation(spriteComp->GetAnimationName())[0].texture;

		//	if (!ResourceManager::GetInstance().GetAnimation(animationComp->GetAnimationName()).empty())
		//	{
		//		sf::Texture t;
		//		animationComp->currentFrameIndex = 0;
		//		animationComp->GetSprite().setTextureRect(ResourceManager::GetInstance().GetAnimation(animationComp->GetAnimationName())[animationComp->currentFrameIndex].textureRect);
		//	}
		//	return;
		//}

		animationComp->currentFrameTime += deltaTime;

		//if (animationComp->currentFrameTime >= ResourceManager::GetInstance().GetAnimation(animationComp->GetAnimationName())[animationComp->currentFrameIndex].duration)
		//	animationComp->currentFrameIndex++; // Next animation frame

		//if (animationComp->currentFrameIndex >= ResourceManager::GetInstance().GetAnimation(animationComp->GetAnimationName()).size())
		//{
		//	if (animationComp->shouldLoop)
		//		animationComp->currentFrameIndex = 0; // Restart animation
		//	//else
		//	//{
		//	//	animationComp->isAnimating = false; // End of animation
		//	//	return;
		//	//}
		//}

		//const auto& frame = ResourceManager::GetInstance().GetAnimation(animationComp->GetAnimationName())[animationComp->currentFrameIndex];

		//animationComp->SetSprite(*frame.texture);
		//animationComp->GetSprite().setTextureRect(frame.textureRect);
	}

}
