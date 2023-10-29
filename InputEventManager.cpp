#include "pch.h"
#include "InputEventManager.h"

namespace LeaderEngine
{
	InputEventManager::InputEventManager()
	{
	}

	InputEventManager::~InputEventManager()
	{
	}

	void InputEventManager::RegisterEvent(INPUT_EVENT inputEvent, InputEventHandler handler)
	{
		_inputEventHandlers[inputEvent].push_back(handler);
	}

	void InputEventManager::UnregisterEvent(INPUT_EVENT inputEvent, InputEventHandler handler)
	{
		auto& handlers = _inputEventHandlers[inputEvent];
		handlers.erase(std::remove(handlers.begin(), handlers.end(), handler)); // reorder the vector to put the handler at the end, then remove it
	}

	void InputEventManager::InvokeEvent(INPUT_EVENT inputEvent, const sf::Event& event)
	{
	    for (auto& handler : _inputEventHandlers[inputEvent])
		{
			handler(event); // for each handler of the input event, invoke it => Call the action associated to the input event
		}
	}
}