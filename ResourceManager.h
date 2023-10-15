#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	class ResourceManager
	{
		public:
			static ResourceManager& GetInstance();

			ResourceManager();
			~ResourceManager();
			void LoadResource(const std::string path);
			const sf::Texture& getTexture(const std::string& id) const;
			//sf::Sprite& getSprite(const std::string& id);
		

		private:
			//static ResourceManager instance;
			//ResourceManager(const ResourceManager& other) = delete; // prevent constructor copy
			//ResourceManager& operator=(const ResourceManager& other) = delete; // prevent copy
			
			void LoadTextures(const YAML::Node& textureNode);
			//sf::Sprite& LoadSprite(const std::string id);
			
			sf::Texture tempTexture;
			std::unordered_map<std::string, sf::Texture> _textures;
			//std::unordered_map<std::string, sf::Sprite> _sprites;
			
	};
}



