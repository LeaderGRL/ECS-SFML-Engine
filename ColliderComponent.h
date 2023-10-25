#pragma once
#include "IComponent.h"
#include "COLLIDER_TYPE.h"
#include "IDrawableComponent.h"

namespace LeaderEngine
{
	class ColliderComponent : public IDrawableComponent
	{
		private :

		protected :
			COLLIDER_TYPE type;
			
		public:
			virtual ~ColliderComponent() = default;
			COLLIDER_TYPE GetColliderType() const { return type; }
			virtual void CheckCollision(ColliderComponent* other) = 0; // Pure
	};
}
