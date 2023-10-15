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
			ResourceManager();
			~ResourceManager();
			void LoadResource(const std::string path);
			sf::Texture& getTexture(std::string id);
		

		private:
			void LoadTextures(const YAML::Node& textureNode);
			
			std::unordered_map<std::string, sf::Texture> _textures;
			
	};
}



