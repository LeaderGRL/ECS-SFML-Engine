#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"
#include <iostream>
#include <typeinfo>

#include "BoxColliderComponent.h"
#include "LuaAPI.h"

namespace LeaderEngine {
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

	void Entity::AddComponent(int type)
	{
		COMPONENT_TYPE c_type = static_cast<COMPONENT_TYPE>(type);

		if (c_type == COMPONENT_TYPE::SPRITE2D)
			AddComponent<Sprite2DComponent>();
		if (c_type == COMPONENT_TYPE::BOX_COLLIDER)
			AddComponent<BoxColliderComponent>(sf::Vector2f(0,0));
			//_components.push_back(std::move(std::shared_ptr<Sprite2DComponent>(static_cast<Sprite2DComponent*>(component))));
	}

	luabridge::LuaRef Entity::GetComponent(int type)
	{

		auto type_c = static_cast<COMPONENT_TYPE>(type);
		if (type_c == COMPONENT_TYPE::SPRITE2D)
			for (const auto& comp : _components)
			{
				if (Sprite2DComponent* spriteComp = dynamic_cast<Sprite2DComponent*>(comp.get()))
				{
					return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState(), spriteComp);
				}

			}

		if (type_c == COMPONENT_TYPE::BOX_COLLIDER)
			for (const auto& comp : _components)
			{
				if (BoxColliderComponent* boxComp = dynamic_cast<BoxColliderComponent*>(comp.get()))
				{
					return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState(), boxComp);
				}

			}
		return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState());
	}

	//void Entity::AddComponent(IComponent* component)
	//{
	//	_components.push_back(std::move(std::shared_ptr<IComponent>(component)));
	//}


	//void Entity::AddComponent(std::unique_ptr<IComponent> component)
	//{
	//	_components.push_back(std::move(component));
	//}

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
