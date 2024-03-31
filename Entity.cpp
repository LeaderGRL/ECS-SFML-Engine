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

	void Entity::Init()
	{
		for (const auto& comp : _components)
		{
			comp.get()->Init(); // Call all component Init()
		}

		// Children
		//for (auto it = _children.begin(); it != _children.end(); it++)
		//{
		//	//std::cout << "name : " << EntityManager::GetInstance().GetName(it->second.get()) << std::endl;
		//	it->second->Init();
		//}

		for (auto& child : _children)
		{
			child.second->Init();
		}
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

	std::vector<std::shared_ptr<IComponent>>& Entity::GetComponents()
	{
		 return _components;
	}

	flatbuffers::Offset<void> Entity::Serialize(flatbuffers::FlatBufferBuilder& builder) const
	{
		std::vector<flatbuffers::Offset<void>> components; // Create a vector of components offsets to know where to find table in the buffer
		std::vector<uint8_t> componentType;

		for (const auto& comp : _components)
		{
			if (const auto serializable = dynamic_cast<ISerializable*>(comp.get()))
			{
				auto componentOffset = serializable->Serialize(builder); // Serialize the component
				auto type = static_cast<uint8_t>(comp.get()->GetType());
				componentType.push_back(type);
				components.push_back(componentOffset.Union()); // Add the offset of the component to the vector
			}

		}

		const auto position = vec2(getPosition().x, getPosition().y);
		const auto scale = vec2(getScale().x, getScale().y);
		const auto componentTypeUnionData = builder.CreateVector(componentType);
		const auto componentUnionData = builder.CreateVector(components);


		const auto transform = CreateTransformSchema(builder, &position, getRotation(), &scale);
		const auto entity = CreateEntitySchema(builder, _id, transform, componentTypeUnionData, componentUnionData);

		builder.Finish(entity);

		return { entity.o };
	}

	void Entity::Deserialize(const void* buffer)
	{
		auto entity = GetEntitySchema(buffer);
		_id = entity->id();
		const auto transform = entity->transform();
		setPosition(transform->position()->x(), transform->position()->y());
		setRotation(transform->rotation());
		setScale(transform->scale()->x(), transform->scale()->y());



	}

	int Entity::GetId() const
	{
		return _id;
	}

	
}
