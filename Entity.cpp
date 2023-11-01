#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"
#include <iostream>

namespace LeaderEngine {
	void Entity::report_errors(lua_State* luaState, int status)
	{
		if (status == 0) {
			return;
		}

		std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(luaState, 1);
	}
	
	Entity::Entity()
	{
		Entity::_id = 0;

		//lua_State* luaState = luaL_newstate(); // Create a lua state

		//luaL_openlibs(luaState); // Open all standard library

		//luabridge::getGlobalNamespace(luaState)
		//	.beginClass<Entity>("Entity")
		//	.addConstructor<void(*) (void)>()
		//	.addFunction("GetId", &Entity::GetId)
		//	.addFunction("PrintNumber", &Entity::PrintNumber)
		//	.endClass();

		//auto globalEntity = std::make_unique<Entity>("test"); // 
		//luabridge::setGlobal(luaState, globalEntity.get(), "Entity");

		//int scriptLoadStatus = luaL_dofile(luaState, "../LeaderEngine/Script.lua"); // Load the script

		//report_errors(luaState, scriptLoadStatus);
	
	}

	Entity::~Entity()
	{
		
	}

	Entity::Entity(std::string name)
	{
		
	}
	
	void Entity::SetId(int id)
	{
		Entity::_id = id;
	}

	void Entity::Update(float deltaTime) const // WARNING : Check if the "const" cannot be a problem in the future
	{
		for (const auto& comp : _components)
		{
			comp.get()->Update(deltaTime); // Call all component Update()
		}
	}

	void Entity::Start()
	{
		
	}

	void Entity::Destroy()
	{
		
	}

	// Draw all drawable components of the entity
	void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.combine(getTransform()); // Apply the entity transform to the drawable components
		for (const auto& comp : _components)
		{
			if (comp->GetType() == COMPONENT_TYPE::DRAWABLE) // Check if the component's type equals DRAWABLE
			{
				const IDrawableComponent* drawable = (IDrawableComponent*)comp.get(); // Cast the component to IDrawable component
				target.draw(*drawable, states); // Draw the drawable component if the cast was successful
			}
		}
	}

	int Entity::PrintNumber()
	{
		return 55;
	}

	//void Entity::AddComponent(std::unique_ptr<IComponent> component)
	//{
	//	_components.push_back(std::move(component)); // Move component into the vector
	//}

	int Entity::GetId() const
	{
		return _id;
	}

	
}