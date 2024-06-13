#include "pch.h"
#include "Entity.h"
#include "Sprite2DComponent.h"
#include <iostream>
#include <memory>
#include <typeinfo>

#include "BoxColliderComponent.h"
#include "CameraComponent.h"
#include "LuaAPI.h"
#include "ScriptComponent.h"

namespace LeaderEngine {
	Entity::Entity()
	{
		Entity::_id = "";

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

	Entity::Entity(const std::string& name)
	{
		Entity::_id = name;
	}
	
	void Entity::SetId(std::string id)
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

	Entity* Entity::AddChild(std::unique_ptr<Entity> child)
	{
		child->SetParent(this);
		Entity* rawPtr = child.get();
		_children[rawPtr->GetId()] = std::move(child); // Add the child to the children map
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
			// Use dynamic_cast to check if the component is drawable
			const IDrawableComponent* drawable = dynamic_cast<const IDrawableComponent*>(comp.get());
			if (drawable != nullptr) // Check if the component's type equals DRAWABLE
			{
				//const IDrawableComponent* drawable = (IDrawableComponent*)comp.get(); // Cast the component to IDrawable component
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
		std::cout << "Serializing Entity" << std::endl;
		std::vector<flatbuffers::Offset<void>> components; // Create a vector of components offsets to know where to find table in the buffer
		std::vector<uint8_t> componentType; // Create a vector of component types to know which component is being serialized
		std::vector<flatbuffers::Offset<EntitySchema>> children; // Create a vector of children offsets to know where to find table in the buffer

		for (const auto& comp : _components)
		{
			if (const auto serializable = dynamic_cast<ISerializable*>(comp.get()))
			{
				std::cout << "COMPONENT : " << typeid(*comp.get()).name() << std::endl;
				auto componentOffset = serializable->Serialize(builder); // Serialize the component
				auto type = static_cast<uint8_t>(comp.get()->GetType());
				componentType.push_back(type);
				components.push_back(componentOffset.Union()); // Add the offset of the component to the vector
			}

		}

		for (const auto& child : _children)
		{
			const auto childOffset = child.second->Serialize(builder);
			children.emplace_back(childOffset.o); // emplace_back is used to avoid copying the object when adding it to the vector
		}

		const auto id = builder.CreateString(_id);
		const auto position = vec2(getPosition().x, getPosition().y);
		const auto scale = vec2(getScale().x, getScale().y);
		const auto componentTypeUnionData = builder.CreateVector(componentType);
		const auto componentUnionData = builder.CreateVector(components);
		const auto childrenData = builder.CreateVector(children);

		const auto transform = CreateTransformSchema(builder, &position, getRotation(), &scale);
		const auto entity = CreateEntitySchema(builder, id, transform, componentTypeUnionData, componentUnionData, childrenData);

		builder.Finish(entity);

		return { entity.o };
	}

	std::shared_ptr<ISerializable> Entity::Deserialize(const void* buffer)
	{
		//std::mutex _mutex;
		//std::lock_guard<std::mutex> lock(_mutex);

		// Validate the buffer
		if (buffer == nullptr)
		{
			std::cerr << "Error: Buffer is null." << std::endl;
			//return;
		}

		//flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t*>(buffer), 1024); // Create a verifier object to verify the buffer
		//if (!VerifyEntitySchemaBuffer(verifier)) // Verify the buffer
		//{
		//	std::cerr << "Error: Buffer verification failed." << std::endl;
		//	return;
		//}

		// Verify the buffer
		//flatbuffers::Verifier verifier(static_cast<const uint8_t*>(buffer), flatbuffers::GetSizePrefixedBufferLength(static_cast<const uint8_t*>(buffer)));
		//if (!VerifyEntitySchemaBuffer(verifier)) {
		//	std::cerr << "Error: Buffer verification failed." << std::endl;
		//	return;
		//}

		const EntitySchema* ent = GetEntitySchema(buffer);
		if (ent == nullptr)
		{
			std::cerr << "Error: Failed to get entity schema." << std::endl;
			//return;
		}

		

		//// Validate the entity schema
		//if (!flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(buffer), flatbuffers::GetSizePrefixedBufferLength(static_cast<const uint8_t*>(buffer))).VerifyBuffer<LeaderEngine::EntitySchema>(nullptr))
		//{
		//	std::cerr << "Error: Buffer verification failed." << std::endl;
		//	return;
		//}

		// Debug: Print buffer information
		std::cout << "Buffer address: " << buffer << std::endl;
		std::cout << "Entity ID: " << ent->id()->c_str() << std::endl; 

		//if (_id != ent->id()->c_str())
		//{
		//	auto entity = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().CreateEntityFromSchema(ent);
		//	SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().AddEntity(std::move(entity));
		//}

		auto entity = SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().CreateEntityFromSchema(ent);
		SceneManager::GetInstance().GetCurrentScene()->GetEntityManager().AddEntity(std::move(entity));

		 
		return std::make_shared<Entity>();
	}



	std::string Entity::GetId() const
	{
		return _id;
	}

	
}
