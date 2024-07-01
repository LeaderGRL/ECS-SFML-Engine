#include "pch.h"
#include "NetworkingComponent.h"

namespace LeaderEngine
{
	NetworkingComponent::NetworkingComponent()
	{
	}

	std::string NetworkingComponent::GetIP() const
	{
		return _ip;
	}

	void NetworkingComponent::SetIP(const std::string& ip)
	{
		_ip = ip;
	}

	bool NetworkingComponent::GetDirty() const
	{
		return isDirty;
	}

	void NetworkingComponent::SetDirty(bool dirty)
	{
		isDirty = dirty;
	}

	void NetworkingComponent::Init()
	{
	}

	void NetworkingComponent::Update(float deltaTime)
	{
	}

	flatbuffers::Offset<void> NetworkingComponent::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		return flatbuffers::Offset<void>();
	}

	std::shared_ptr<ISerializable> NetworkingComponent::Deserialize(const void* buffer)
	{
		return std::shared_ptr<ISerializable>();
	}

	COMPONENT_TYPE NetworkingComponent::GetType() const
	{
		return COMPONENT_TYPE::NETWORKING;
	}

	//void NetworkingComponent::Serialize()
	//{
	//	flatbuffers::FlatBufferBuilder builder;

	//	 
	//}


}
