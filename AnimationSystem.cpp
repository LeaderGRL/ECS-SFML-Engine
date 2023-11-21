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
				continue;

			if (!spriteComp->isAnimating)
			{
				//const sf::Texture* texture = rs.GetAnimation(spriteComp->GetAnimationName())[0].texture;

				if (!ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName()).empty())
				{
					sf::Texture t;
					spriteComp->currentFrameIndex = 0;
					spriteComp->GetSprite().setTextureRect(ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex].textureRect);
				}
				continue;
			}

			spriteComp->currentFrameTime += deltaTime;

			if (spriteComp->currentFrameTime >= ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex].duration)
				spriteComp->currentFrameIndex++; // Next animation frame

			if (spriteComp->currentFrameIndex >= ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName()).size())
			{
				if (spriteComp->shouldLoop)
					spriteComp->currentFrameIndex = 0; // Restart animation
				else
				{
					spriteComp->isAnimating = false; // End of animation
					continue;
				}
			}

			const auto& frame = ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex];

			spriteComp->SetSprite(*frame.texture);
			spriteComp->GetSprite().setTextureRect(frame.textureRect);
		}
	}
}