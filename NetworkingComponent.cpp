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


	void NetworkingComponent::Init()
	{
	}

	void NetworkingComponent::Update(float deltaTime)
	{
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
