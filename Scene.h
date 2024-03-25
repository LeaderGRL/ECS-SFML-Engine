#pragma once
#include "EntityManager.h"

namespace LeaderEngine
{
	class Scene
	{
		private:
			std::string _sceneID;
			EntityManager _entityManager;

		public:
			Scene();
			~Scene();

			void Init();
			void Pause();
			void Resume();
			void Update(float deltaTime);
			void Draw(sf::RenderTarget& target, sf::RenderStates states);

			void SetSceneID(const std::string& sceneID);
			std::string GetSceneID() const;
			EntityManager& GetEntityManager();
			
	};
}

