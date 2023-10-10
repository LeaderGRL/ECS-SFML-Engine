#pragma once
#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
	class IComponent {
		public:
			virtual ~IComponent() { };
			virtual COMPONENT_TYPE GetType() const = 0;
	};
}
