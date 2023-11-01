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

	EventManager& EventManager::GetInstance()
	{
		static EventManager instance;
		return instance;
	}
	
	void EventManager::RegisterEvent(INPUT_EVENT inputEvent, const EventHandler& handler)
	{
		_EventHandlers[inputEvent].push_back(std::make_shared<EventHandler>(handler));
	}

	void EventManager::UnregisterEvent(INPUT_EVENT inputEvent, EventHandler& handler)
	{
		// We make witchcraft comparaison cause there is no == operator for std::function
		
		// Reorder the vector to put the handler at the end if the current item explored is equal to handler
		auto& handlers = _EventHandlers[inputEvent];
		handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
			[&handler](const std::shared_ptr<EventHandler>& item) {
				return item->target_type() == handler.target_type() // Ensure the callable targets contained within the two std::function objects have the same type.
					&& item->target<void(const sf::Event&)>() == handler.target<void(const sf::Event&)>(); // Ensure the callable targets themselves are the same
			}), handlers.end()); 
	}

	void EventManager::InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event)
	{
	    for (const auto& handler : _EventHandlers[inputEvent])
		{
			(*handler)(event); // for each dereferenced handler of the input event, invoke it => Call the action associated to the input event
		}
	}
}