#include "pch.h"
#include "NetworkingComponent.h"

namespace LeaderEngine
{
	NetworkingComponent::NetworkingComponent()
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
