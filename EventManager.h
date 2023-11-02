#pragma once
#include <SFML/window.hpp>
#include <functional>
#include "INPUT_EVENT.h"
#include "lua.hpp"
#include "luabridge3/LuaBridge/LuaBridge.h"

namespace LeaderEngine
{
	class EventManager
	{
		public:
			static EventManager& GetInstance();
			
			EventManager();
			~EventManager();

			using EventHandler = std::function<void(const sf::Event&)>; // declare a type for the input event handler function

			void RegisterEvent(INPUT_EVENT inputEvent, const EventHandler& handler); // add a handler to the list of handlers => Equivalent to subscribe event in C#
			void RegisterEvent(int inputEvent, luabridge::LuaRef callback); // Register event from Lua Script

			void UnregisterEvent(INPUT_EVENT inputEvent, EventHandler& handler); // remove a handler from the list of handlers

			void InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event); // handle an input event

		private:
			std::unordered_map<INPUT_EVENT, std::vector<std::shared_ptr<EventHandler>>> _EventHandlers; // list of handlers for each input event
	};
}

