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
		//std::lock_guard<std::mutex> lock(_mutex);
		_eventHandlers[inputEvent].push_back(std::make_shared<EventHandler>(handler));
	}

	void EventManager::RegisterEvent(int inputEvent, const luabridge::LuaRef &callback)
	{
		//luabridge::Result itemsPushed = luabridge::Stack<sf::Event>::push(LuaAPI::GetInstance().GetLuaState(), sf::Event()); // Push the event onto the lua stack


		//const auto& event = static_cast<INPUT_EVENT>(inputEvent);
		auto handler = [callback](const sf::Event& e) mutable 
		{
			if (callback.isFunction())
			{
				try
				{
					//luabridge::Result itemsPushed = luabridge::Stack<sf::Event>::push(LuaAPI::GetInstance().GetLuaState(), e); // Push the event onto the lua stack

					const auto test = callback(e);
					std::cout<< "garbage : " << lua_gc(LuaAPI::GetInstance().GetLuaState(), 3); // Garbage collection to avoid memory leaks in Lua script
					lua_gc(LuaAPI::GetInstance().GetLuaState(), 0);


					std::cerr << "error : " << test.errorCode() << test.errorMessage() << std::endl;
				}
				catch (luabridge::LuaException const& e)
				{
					std::cerr << "Error calling Lua event handler: " << e.what() << std::endl;
				}
				catch (std::exception const& e)
				{
					std::cerr << "Error calling Lua event handler: " << e.what() << std::endl;
				}
				catch (...)
				{
					std::cerr << "Error calling Lua event handler: " << "Unknown error" << std::endl;
				}
				
				//luabridge::Result itemsPushed = luabridge::Stack<sf::Event>::push(LuaAPI::GetInstance().GetLuaState(), e); // Push the event onto the lua stack
 
				//callback(e);

				//if (lua_pcall(LuaAPI::GetInstance().GetLuaState(), 1, 0, 0) != LUA_OK) {
				//	// Handle error, pop the error message from the stack
				//	const char* error_msg = lua_tostring(LuaAPI::GetInstance().GetLuaState(), -1);
				//	std::cerr << "Error calling Lua event handler: " << error_msg << std::endl;
				//	lua_pop(LuaAPI::GetInstance().GetLuaState(), 1); // Pop the error message
				//}
			}
		};
		
		RegisterEvent(static_cast<INPUT_EVENT>(inputEvent), handler);
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
		std::cout << "Invoking event" << std::endl;
		//std::lock_guard<std::mutex> lock(_mutex);
		// Copy the handlers to avoid issues with handlers that might register/unregister during invocation
		//auto handlersCopy = _eventHandlers[inputEvent];

		if (_eventHandlers.find(inputEvent) != _eventHandlers.end()) {
			auto handlersCopy = _eventHandlers[inputEvent];
			for (const auto& handler : handlersCopy) {
				try
				{
					(*handler)(event);
				}
				catch (const std::exception& e)
				{
					std::cerr << "Error invoking event: " << e.what() << std::endl;
				}
				catch (const luabridge::LuaException& e)
				{
					std::cerr << "Error invoking event: " << e.what() << std::endl;
				}
				catch (const std::string& e)
				{
					std::cerr << "Error invoking event: " << e << std::endl;
				}
				catch (const char* e)
				{
					std::cerr << "Error invoking event: " << e << std::endl;
				}
				catch (...)
				{
					std::cerr << "Error invoking event: " << "Unknown error" << std::endl;
				}
			}
		}

		// Now iterate over the copy safely
		//for (const auto& handler : handlersCopy)
		//{
		//	(*handler)(event); // dereference the handler because it's a shared_ptr to a std::function object
		//}
	}


	/*std::vector<std::unique_ptr<std::function<void(const sf::Event&)>>> EventManager::GetEventFromInput(INPUT_EVENT input_event)
	{
		return _EventHandlers[input_event];
	}*/
	
	
}
