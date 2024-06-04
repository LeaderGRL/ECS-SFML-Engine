#pragma once
#include <SFML/window.hpp>
#include <functional>
#include "INPUT_EVENT.h"
#include "lua.hpp"
#include "luabridge3/LuaBridge/LuaBridge.h"
#include "LuaAPI.h"

namespace LeaderEngine
{
	class EventManager
	{
		public:
			static EventManager& GetInstance();
			
			EventManager();
			~EventManager();
			EventManager(EventManager const&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager& operator=(EventManager const&) = delete;
			EventManager& operator=(EventManager&&) = delete;

			using EventHandler = std::function<void(const sf::Event&)>; // declare a type for the input event handler function
			EventHandler handler;

			void RegisterEvent(INPUT_EVENT inputEvent, const EventHandler& handler); // add a handler to the list of handlers => Equivalent to subscribe event in C#
			void RegisterEvent(int inputEvent, const luabridge::LuaRef &callback); // Register event from Lua Script

			void UnregisterEvent(INPUT_EVENT inputEvent, const EventHandler& handler); // remove a handler from the list of handlers

			void InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event); // handle an input event
			//std::vector<std::shared_ptr<std::function<void(const sf::Event&)>>> GetEventFromInput(INPUT_EVENT);

		private:
			std::unordered_map<INPUT_EVENT, std::vector<std::shared_ptr<EventHandler>>> _eventHandlers; // list of handlers for each input event
			std::mutex _mutex;
	};
}

