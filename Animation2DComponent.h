#pragma once
#include "Sprite2DComponent.h"
#include "Animation2DComponentSchema_generated.h"

namespace LeaderEngine
{
	class Animation2DComponent : public Sprite2DComponent
	{
		private:
			std::string _animationName;

		public:
			Animation2DComponent();
			Animation2DComponent(const std::string& animationName, bool loop);
			~Animation2DComponent();

			bool shouldLoop = true;
			int currentFrameIndex = 0;
			float currentFrameTime = 0;

			void PlayAnimation(bool loop = true);
			void StopAnimation();

			std::string& GetAnimationName() ;
			void SetAnimationName(const std::string& animationName);

			void Serialize(flatbuffers::FlatBufferBuilder& builder) const override;
			void Deserialize(const void* buffer) override;
	};

}

