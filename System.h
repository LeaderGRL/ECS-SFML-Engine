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
			void AddEntity(Entity entity);
			void RemoveEntity(Entity entity);
			std::vector<Entity> GetEntities();
			virtual void Update() = 0;
	};
}