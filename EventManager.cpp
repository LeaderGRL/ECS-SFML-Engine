#include "pch.h"
#include "EventManager.h"

namespace LeaderEngine
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	EventManager EventManager::GetInstance()
	{
		static EventManager instance;
		return instance;
	}
	
	void EventManager::RegisterEvent(INPUT_EVENT inputEvent, EventHandler handler)
	{
		_EventHandlers[inputEvent].push_back(handler);
	}

	void EventManager::UnregisterEvent(INPUT_EVENT inputEvent, EventHandler handler)
	{
		auto& handlers = _EventHandlers[inputEvent];
		//handlers.erase(std::remove(handlers.begin(), handlers.end(), handler)); // reorder the vector to put the handler at the end, then remove it
	}

	void EventManager::InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event)
	{
	    for (auto& handler : _EventHandlers[inputEvent])
		{
			handler(event); // for each handler of the input event, invoke it => Call the action associated to the input event
		}
	}
}