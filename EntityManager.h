#pragma once
#include "Entity.h"
#include <unordered_map>

namespace LeaderEngine
{
	class EntityManager
	{
		private:
			std::unordered_map<std::string, std::unique_ptr<Entity>> _entities;
			static EntityManager& instance();
		protected:
			
		public:
			EntityManager();
			~EntityManager();
			//void AddEntity(Entity&& entity); // RValue reference
			Entity* CreateEntity(std::string name);
			Entity* GetEntity(const std::string& name);
			const std::unordered_map<std::string, std::unique_ptr<Entity>>& GetEntities() const;
			void draw(sf::RenderTarget& target, sf::RenderStates states);
			void Update(float deltaTime);
			/*void RemoveEntity(Entity& entity);
			void RemoveAllEntities();*/
			//void RemoveEntity(Entity&& entity);
			//std::unique_ptr<Entity> GetEntity(std::string name);
			//const std::vector<Entity>& GetEntities() const; // Return a reference to the vector of entities
			//Entity* GetEntityById(int id); // Return a pointer to an Entity that allow to modify it
			//virtual void Update() = 0;
	};
}