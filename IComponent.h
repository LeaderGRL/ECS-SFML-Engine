#pragma once
#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
	class IComponent {
		public:
			virtual ~IComponent() = default;
			virtual void Update(int deltaTime) = 0;
			virtual COMPONENT_TYPE GetType() const = 0;
	};
}
