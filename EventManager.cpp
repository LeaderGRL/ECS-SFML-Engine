#include "pch.h"
#include "EventManager.h"

#include <queue>

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

	void EventManager::RegisterEvent(int inputEvent, const luabridge::LuaRef &callback)
	{	
		const auto& event = static_cast<INPUT_EVENT>(inputEvent);
		handler = [callback](const sf::Event& e) mutable 
		{
			if (callback.isFunction())
			{
				luabridge::Result itemsPushed = luabridge::Stack<sf::Event>::push(LuaAPI::GetInstance().GetLuaState(), e); // Push the event onto the lua stack

				callback(e);
				//if (lua_pcall(LuaAPI::GetInstance().GetLuaState(), 1, 0, 0) != LUA_OK) {
				//	// Handle error, pop the error message from the stack
				//	const char* error_msg = lua_tostring(LuaAPI::GetInstance().GetLuaState(), -1);
				//	std::cerr << "Error calling Lua event handler: " << error_msg << std::endl;
				//	lua_pop(LuaAPI::GetInstance().GetLuaState(), 1); // Pop the error message
				//}
			}
		};
		
		RegisterEvent(event, handler);
	}

	void EventManager::UnregisterEvent(INPUT_EVENT inputEvent, const EventHandler& handler)
	{
		// We make witchcraft comparaison cause there is no == operator for std::function
		
		// Reorder the vector to put the handler at the end if the current item explored is equal to handler
		//auto& handlers = _EventHandlers[inputEvent];
		//handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
		//	[&handler](const std::shared_ptr<EventHandler>& item) {
		//		return item->target_type() == handler.target_type() // Ensure the callable targets contained within the two std::function objects have the same type.
		//			&& item->target<void(const sf::Event&)>() == handler.target<void(const sf::Event&)>(); // Ensure the callable targets themselves are the same
		//	}), handlers.end()); 
	}

	void EventManager::InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event)
	{
		// Copy the handlers to avoid issues with handlers that might register/unregister during invocation
		auto handlersCopy = _EventHandlers[inputEvent];

		// Now iterate over the copy safely
		for (const auto& handler : handlersCopy)
		{
			(*handler)(event);
		}
	}


	/*std::vector<std::unique_ptr<std::function<void(const sf::Event&)>>> EventManager::GetEventFromInput(INPUT_EVENT input_event)
	{
		return _EventHandlers[input_event];
	}*/
	
	
}
