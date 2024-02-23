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
			bool isAuthoritative; // Is this the server?
			bool isDirty; // Has the entity changed?
		public:
			NetworkingComponent();
			~NetworkingComponent();
			
			void Update(float deltaTime) override;

			//void Serialize();
			//void Deserialize();
			
		 
	};
}
