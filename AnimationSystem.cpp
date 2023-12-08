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
		Sprite2DComponent* spriteComp = entity->GetComponent<Sprite2DComponent>();

		if (!spriteComp)
			return;

		if (!spriteComp->isAnimating)
		{
			//const sf::Texture* texture = rs.GetAnimation(spriteComp->GetAnimationName())[0].texture;

			if (!ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName()).empty())
			{
				sf::Texture t;
				spriteComp->currentFrameIndex = 0;
				spriteComp->GetSprite().setTextureRect(ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex].textureRect);
			}
			return;
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
				return;
			}
		}

		const auto& frame = ResourceManager::GetInstance().GetAnimation(spriteComp->GetAnimationName())[spriteComp->currentFrameIndex];

		spriteComp->SetSprite(*frame.texture);
		spriteComp->GetSprite().setTextureRect(frame.textureRect);
	}

}