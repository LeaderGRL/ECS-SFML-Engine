#pragma once
#include "IComponent.h"
#include "ISerializable.h"
#include "SFML/Network.hpp"
#include "flatbuffers/flatbuffers.h"

namespace LeaderEngine
{
	class NetworkingComponent : public IComponent, public ISerializable
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

			bool GetDirty() const;
			void SetDirty(bool dirty);

			void Init() override;
			void Update(float deltaTime) override;

			flatbuffers::Offset<void> Serialize(flatbuffers::FlatBufferBuilder& builder) const override;
		    std::shared_ptr<ISerializable> Deserialize(const void* buffer) override;

			COMPONENT_TYPE GetType() const;

	};
}

