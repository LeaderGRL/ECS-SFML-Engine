#include "pch.h"
#include "EntityManager.h"

#include "Animation2DComponent.h"
#include "CollisionSystem.h"
#include "NetworkingComponent.h"

using namespace std;

namespace LeaderEngine
{	
	//EntityManager& EntityManager::GetInstance()
	//{
	//	static EntityManager instance;
	//	return instance;
	//}

	EntityManager::EntityManager()
	{
		
	}

	EntityManager::~EntityManager()
	{
		
	}
	
	Entity* EntityManager::CreateEntity(const std::string& name)
	{
		std::string id = name;
		if (IdExists(id))
		{
			int i = 1;
			while (IdExists(id + std::to_string(i)))
			{
				i++;
			}
			id = id + std::to_string(i);

		}
		std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(id);
		Entity* rawPtr = newEntity.get();
		_entities[id] = std::move(newEntity);
		//_entities.insert(std::make_pair(name, newEntity));
		return rawPtr;
	}

	void EntityManager::AddEntity(std::unique_ptr<Entity> entity)
	{
		//std::unique_ptr<Entity> newEntity = std::move(entity);
		const Entity* rawPtr = entity.get();
		_entities[rawPtr->GetId()] = std::move(entity);
	}

	std::unique_ptr<Entity> EntityManager::CreateEntityFromSchema(const EntitySchema* entitySchema)
	{
		std::cout << "Creating entity from schema" << std::endl;
		std::unique_ptr<Entity> newEntity = std::make_unique<Entity>(entitySchema->id()->c_str());
		newEntity->SetId(entitySchema->id()->c_str());
		newEntity->setPosition(sf::Vector2f(entitySchema->transform()->position()->x(), entitySchema->transform()->position()->y()));
		newEntity->setScale(sf::Vector2f(entitySchema->transform()->scale()->x(), entitySchema->transform()->scale()->y()));
		newEntity->setRotation(entitySchema->transform()->rotation());

		const auto componentType = entitySchema->components_type();
		const auto componentData = entitySchema->components();
		const auto children = entitySchema->children();

		//auto verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(componentData->data()), componentData->size());
		//if (!VerifySprite2DComponentSchemaBuffer(verifier))
		//{
		//	std::cerr << "Error: The buffer is not a valid Sprite2DComponent schema." << std::endl;
		//	//return;
		//}

		 for (size_t i = 0; i < componentType->size(); ++i)
		 {
		 	const auto type = static_cast<COMPONENT_TYPE>(componentType->Get(i));
		 	const auto data = componentData->Get(i);

		 	switch (type)
		 	{
				case COMPONENT_TYPE::ANIMATION2D:
				{
					std::cout << "Creating animation component" << std::endl;
					const auto animation = reinterpret_cast<const Animation2DComponentSchema*>(data);
					std::cout << "Animation Component - name: " << animation->animation_name()->c_str() << std::endl;
					newEntity->AddComponent<Animation2DComponent>(animation->animation_name()->c_str(), animation->should_loop(), animation->is_animating());
					break;
				}
		 		case COMPONENT_TYPE::SPRITE2D:
				{
					std::cout << "Creating drawable component" << std::endl;
					const auto sprite = reinterpret_cast<const Sprite2DComponentSchema*>(data);
					std::cout << "Sprite Component - texture: " << sprite->texture_name()->c_str() << std::endl;
					newEntity->AddComponent<Sprite2DComponent>(sprite->texture_name()->c_str());
					break;
				}
					
				
		 		/*default:
					std::cout << "Unknown component type";
					break;*/
		 	}
		 }

		for (size_t i = 0; i < children->size(); ++i)
		{
			const auto child = children->Get(i);
			auto childEntity = CreateEntityFromSchema(child); // Recursively create child entities
			newEntity->AddChild(std::move(childEntity));
		}

		std::cout << "TEST !" << std::endl;

		return newEntity;
	}

	Entity* EntityManager::GetEntity(const std::string& name)
	{
		const auto it = _entities.find(name);
		if (it != _entities.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	const std::string EntityManager::GetName(const Entity* entity)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if (it->second.get() == entity)
			{
				return it->first;
			}
		}
		return "";
	}

	const std::unordered_map<std::string, std::unique_ptr<Entity>>& EntityManager::GetEntities() const
	{
		return _entities;
	}

	bool EntityManager::IdExists(const std::string& id) const
	{
		for (const auto& entity : _entities)
		{
			if (entity.first == id)
			{
				return true;
			}
		}

		return false;
	}

	void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states)
	{
		for (auto it = _entities.begin(); it != _entities.end(); it++)
		{
			it->second->draw(target, states);
		}
	}

	void EntityManager::Init()
	{
		for (auto it = _entities.begin(); it != _entities.end(); it++)
		{
			it->second->Init();
		}
	}

	void EntityManager::Update(float deltaTime)
	{
		_collisionSystem.CheckCollisions(_entities);
		_animationSystem.Update(_entities, deltaTime);
		for (auto it = _entities.begin(); it != _entities.end(); it++)
		{
			it->second->Update(deltaTime);
			
		}
	}

	//void EntityManager::RemoveEntity(Entity& entity)
	//{
	//	// Rearranges the elements, moving the ones to be erased to the end.
	//	_entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end());
	//}

	//void EntityManager::RemoveAllEntities()
	//{
	//	_entities.clear();
	//}

	//std::unique_ptr<Entity> EntityManager::GetEntity(std::string name)
	//{
	//	return _entities[name];
	//}
	
	// First const make sure that the return value is not modifiable
	// Second const make sure that the function does not modify the class
	// & means that the function does not copy the class => Reference to the _entities vector rather than a copy of it
	/*const std::vector<Entity>& EntityManager::GetEntities() const
	{
		return _entities;
	}*/

	/*Entity* EntityManager::GetEntityById(int id)
	{
		for (auto& entity : _entities)
		{
			if (entity.GetId() == id)
			{
				return &entity;
			}
		}

		return nullptr;
	}*/
	
	//bool operator==(const Entity& lhs, const Entity& rhs)
	//{
	//	return lhs.GetId() == rhs.GetId();
	//}

}
