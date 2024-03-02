#pragma once
#include "EntityManager.h"

namespace LeaderEngine
{
	class Scene
	{
		private:
			int _sceneID;
			EntityManager _entityManager;

		public:
			Scene();
			~Scene();

			void Init();
			void Pause();
			void Resume();
			void Update(float deltaTime);
			void Draw(sf::RenderTarget& target, sf::RenderStates states);

			EntityManager& GetEntityManager();
			
	};
}

