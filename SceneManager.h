#pragma once
#include <stack>

#include "Scene.h"

namespace LeaderEngine
{
	class SceneManager
	{
		private:
			std::stack<std::unique_ptr<Scene>> _scenes;


		public:
			SceneManager();
			~SceneManager();

			void PushScene(std::unique_ptr<Scene> scene);
			void PopScene();
			void ChangeScene(std::unique_ptr<Scene> scene);
			Scene* GetCurrentScene();
			void Update(float deltaTime);
			void Draw(sf::RenderTarget& target, sf::RenderStates states);
			
	};
}

