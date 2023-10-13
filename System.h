#pragma once
#include "Entity.h"

namespace LeaderEngine
{
	class EntityManager
	{
		private:
			std::vector<Entity> _entities;
		protected:
			
		public:
			EntityManager();
			~EntityManager();
			void AddEntity(Entity&& entity); // RValue reference
			void RemoveEntity(Entity& entity);
			void RemoveAllEntities();
			//void RemoveEntity(Entity&& entity);
			const std::vector<Entity>& GetEntities() const; // Return a reference to the vector of entities
			Entity* GetEntityById(int id); // Return a pointer to an Entity that allow to modify it
			//virtual void Update() = 0;
	};
}