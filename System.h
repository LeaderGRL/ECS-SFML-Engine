#pragma once
#include "Entity.h"

namespace LeaderEngine
{
	class System
	{
		private:
			std::vector<Entity> _entities;
		protected:
			
		public:
			System();
			~System();
			void AddEntity(Entity&& entity); // RValue reference
			void RemoveEntity(Entity& entity);
			void RemoveAllEntities();
			//void RemoveEntity(Entity&& entity);
			const std::vector<Entity>& GetEntities() const; // Return a reference to the vector of entities
			//virtual void Update() = 0;
	};
}