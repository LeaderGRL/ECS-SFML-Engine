#pragma once
#include <memory>
#include <string>
#include "COMPONENT_TYPE.h"

namespace LeaderEngine
{
    class Entity;

    class IComponent {
        protected:
			std::string parent;

		public:
			virtual ~IComponent() = default;
			virtual void Init() = 0;
			virtual void Update(float deltaTime) = 0;
			virtual COMPONENT_TYPE GetType() const = 0;

			void setParent(std::string parent)
			{
				this->parent = parent;
			}

			/**
			 * \brief WARNING RETURNS NULLPTR IF PARENT NOT ASSIGNED
			 * \return
			 */
			std::string getParent()
			{
				return parent;
			}
	};
}
