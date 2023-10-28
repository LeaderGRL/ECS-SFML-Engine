#include "pch.h"
#include "AnimationSystem.h"

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
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			Sprite2DComponent* spriteComp = it->second->GetComponent<Sprite2DComponent>();

			if (!spriteComp)
				return;

			if (!spriteComp->isAnimating)
			{
				return;
			}

			spriteComp->currentFrameTime += deltaTime;

			if (spriteComp->currentFrameTime >= rs.GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex].duration)
				spriteComp->currentFrameIndex++; // Next animation frame

			if (spriteComp->currentFrameIndex >= rs.GetAnimation(spriteComp->GetAnimationName()).size())
			{
				if (spriteComp->shouldLoop)
					spriteComp->currentFrameIndex = 0; // Restart animation
				else
				{
					spriteComp->isAnimating = false; // End of animation
					continue;
				}
			}
		}
	}
}