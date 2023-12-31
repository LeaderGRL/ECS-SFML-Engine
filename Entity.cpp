#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"
#include <iostream>
#include <typeinfo>

#include "BoxColliderComponent.h"
#include "CameraComponent.h"
#include "LuaAPI.h"
#include "ScriptComponent.h"

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

	void Entity::SetParent(Entity* parent)
	{
		_parent = parent;
	}

	Entity* Entity::GetParent() const
	{
		return _parent;
	}

	Entity* Entity::AddChild(const std::string& name)
	{
		//Entity child = EntityManager::GetInstance().CreateEntity(name);

		std::unique_ptr<Entity> child = std::make_unique<Entity>(name);
		child->SetParent(this);

		Entity* rawPtr = child.get();
		_children[name] = std::move(child);

		return rawPtr;
	}

	Entity* Entity::GetChild(const std::string& name)
	{
		std::cout << name << std::endl;
		const auto it = _children.find(name);
		if (it != _children.end())
		{
			std::cout << it->first << std::endl;
			return it->second.get();
		}
		return nullptr;
	}

	std::unordered_map<std::string, std::unique_ptr<Entity>>& Entity::GetChildren()
	{
		return _children;
	}

	void Entity::RemoveChild(const std::string& name)
	{
		
	}

	void Entity::Update(float deltaTime) const // WARNING : Check if the "const" cannot be a problem in the future
	{
		for (const auto& comp : _components)
		{
			comp.get()->Update(deltaTime); // Call all component Update()
		}

		// Children
		//for (auto it = _children.begin(); it != _children.end(); it++)
		//{
		//	//std::cout << "name : " << EntityManager::GetInstance().GetName(it->second.get()) << std::endl;
		//	it->second->Update(deltaTime);
		//}

		for (auto& child : _children) {
			child.second->Update(deltaTime);
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

		// Children
		//for (auto it = _children.begin(); it != _children.end(); it++)
		//{
		//	//std::cout << "name : " << EntityManager::GetInstance().GetName(this) << std::endl;
		//	it->second->draw(target, states);
		//}

		for (auto& child : _children) {
			child.second->draw(target, states); // recursive call
		}
	}

	//--------------------------- TO REFACTOR ---------------------------//

	/*void Entity::AddComponent(int type)
	{
		COMPONENT_TYPE c_type = static_cast<COMPONENT_TYPE>(type);

		if (c_type == COMPONENT_TYPE::SPRITE2D)
			AddComponent<Sprite2DComponent>();
		if (c_type == COMPONENT_TYPE::BOX_COLLIDER)
			AddComponent<BoxColliderComponent>(sf::Vector2f(0,0));
		if (c_type == COMPONENT_TYPE::ANIMATION)
			AddComponent<Sprite2DComponent>();
		if (c_type == COMPONENT_TYPE::CAMERA)
			AddComponent<CameraComponent>();
		if (c_type == COMPONENT_TYPE::SCRIPT)
			AddComponent<ScriptComponent>();
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

		if (type_c == COMPONENT_TYPE::ANIMATION)
			for (const auto& comp : _components)
			{
				if (Sprite2DComponent* animComp = dynamic_cast<Sprite2DComponent*>(comp.get()))
				{
					return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState(), animComp);
				}
			}

		if (type_c == COMPONENT_TYPE::CAMERA)
			for (const auto& comp : _components)
			{
				if (CameraComponent* camComp = dynamic_cast<CameraComponent*>(comp.get()))
				{
					return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState(), camComp);
				}
			}
		if (type_c == COMPONENT_TYPE::SCRIPT)
			for (const auto& comp : _components)
			{
				if (ScriptComponent* scriptComp = dynamic_cast<ScriptComponent*>(comp.get()))
				{
					return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState(), scriptComp);
				}
			}

		return luabridge::LuaRef(LuaAPI::GetInstance().GetLuaState());
	}*/

	// -------------------------------------------------------------------- //

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
