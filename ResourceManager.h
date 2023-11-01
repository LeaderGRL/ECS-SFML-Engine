#pragma once
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace LeaderEngine
{
	struct AnimationFrame {
		sf::Texture* texture; // Reference to a portion of a texture
		sf::IntRect textureRect;
		float duration; // Duration for which this frame should be shown
	};

	class ResourceManager
	{
		public:
			static ResourceManager& GetInstance();

			ResourceManager();
			~ResourceManager();
			ResourceManager(ResourceManager const&) = delete;
			ResourceManager(ResourceManager&&) = delete;
			ResourceManager& operator=(ResourceManager const&) = delete;
			ResourceManager& operator=(ResourceManager&&) = delete;
			void LoadResource(const std::string path);
			const sf::Texture& getTexture(const std::string& id) const;
			const std::vector<AnimationFrame>& GetAnimation(const std::string& id) const;
			//sf::Sprite& getSprite(const std::string& id);
		

		private:	
			void LoadTextures(const YAML::Node& textureNode);
			void LoadAnimation(const YAML::Node& animationNode);
			//sf::Sprite& LoadSprite(const std::string id);
			//void LoadAnimation(const YAML::Node& animationNode, int frameWidth, int frameHeight, float speed);
			
			sf::Texture tempTexture;
			std::unordered_map<std::string, sf::Texture> _textures;
			std::unordered_map<std::string, std::vector<AnimationFrame>> _animations; // All animation sequences
			//std::unordered_map<std::string, sf::Sprite> _sprites;
			
	};
}



