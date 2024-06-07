#pragma once
#include "Entity.h"
#include <unordered_map>
#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "NetworkingSystem.h"

namespace LeaderEngine
{
	class EntityManager
	{
		private:
			std::unordered_map<std::string, std::unique_ptr<Entity>> _entities;
			CollisionSystem _collisionSystem;
			AnimationSystem _animationSystem;
			//NetworkingSystem _networkSystem;
			//static EntityManager& instance();
		protected:
			
		public:
			//static EntityManager& GetInstance();
			
			EntityManager();
			~EntityManager();
			//EntityManager(EntityManager const&) = delete;
			//EntityManager(EntityManager&&) = delete;
			//EntityManager& operator=(EntityManager const&) = delete;
			//EntityManager& operator=(EntityManager&&) = delete;

			//void AddEntity(Entity&& entity); // RValue reference
			Entity* CreateEntity(std::string name);
			void AddEntity(std::unique_ptr<Entity> entity);
			std::unique_ptr<Entity> CreateEntityFromSchema(const EntitySchema* entitySchema);
			//std::shared_ptr<Entity> CreateEntity(std::string name);
			Entity* GetEntity(const std::string& name);
			const std::string GetName(const Entity* entity);
			const std::unordered_map<std::string, std::unique_ptr<Entity>>& GetEntities() const;
			void draw(sf::RenderTarget& target, sf::RenderStates states);

			void Init();
			void Update(float deltaTime);

			
	};
}