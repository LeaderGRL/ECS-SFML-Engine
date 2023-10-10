#include "pch.h"
#include "AComponent.h"

namespace LeaderEngine
{
	AComponent::AComponent()
	{
		AComponent::_id = 0;
	}

	AComponent::~AComponent()
	{
	}

	void AComponent::SetId(int id)
	{
		AComponent::_id = id;
	}

	int AComponent::GetId()
	{
		return _id;
	}


}