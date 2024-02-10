#include "pch.h"
#include "SystemManager.h"

namespace LeaderEngine
{
	SystemManager& SystemManager::GetInstance()
	{
		static SystemManager instance;
		return instance;
	}
}
