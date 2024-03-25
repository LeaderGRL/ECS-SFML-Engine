#pragma once
#include "IComponent.h"
#include "SFML/Network.hpp"
#include "flatbuffers/flatbuffers.h"

namespace LeaderEngine
{
	class NetworkingComponent : public IComponent
	{
		private:
			int _id;
			std::string _ip;
			bool isAuthoritative; // Is this the server?
			bool isDirty; // Has the entity changed?
		public:
			NetworkingComponent();

			std::string GetIP() const;
			void SetIP(const std::string& ip);
			void Update(float deltaTime) override;
			COMPONENT_TYPE GetType() const;

	};
}

