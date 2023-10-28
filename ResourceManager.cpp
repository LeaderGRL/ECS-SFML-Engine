#include "pch.h"
#include "ResourceManager.h"
#include <iostream>
#include <filesystem>

namespace LeaderEngine
{
	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}
	ResourceManager::ResourceManager()
	{
		
	}

	ResourceManager::~ResourceManager()
	{
	}

	void ResourceManager::LoadResource(const std::string path)
	{
		YAML::Node resource = YAML::LoadFile(path);

		if (resource["textures"])
			LoadTextures(resource["textures"]);

		if (resource["animations"])
			LoadAnimation(resource["animations"]);
	}

	const sf::Texture& ResourceManager::getTexture(const std::string& id) const
	{
		//if (!_textures.contains(id))
		//{
		//	std::cerr << "Texture with id " << id << " does not exist" << std::endl;
		//}

		sf::Texture placeholderTexture;

		auto it = _textures.find(id);
		if (it != _textures.end()) {
			return it->second;
		}
		std::cout << "Fail to find texture with id " << id << std::endl;
		return placeholderTexture;
		
		//return _textures.at(id);
	}

	const std::vector<AnimationFrame>& ResourceManager::GetAnimation(const std::string& id) const
	{	
		auto it = _animations.find(id);
		if (it != _animations.end())
		{
			return it->second;
		}

		return std::vector<AnimationFrame>(); // return empty vector if not found
	}

	//sf::Sprite& ResourceManager::getSprite(const std::string& id)
	//{
	//	// TODO: insert return statement here
	//}

	void ResourceManager::LoadTextures(const YAML::Node& textureNode)
	{
		for (const YAML::Node& texture : textureNode)
		{
			std::string id = texture["id"].as<std::string>();
			std::string path = texture["path"].as<std::string>();

			std::cout << "Loading texture " << id << " from " << path << std::endl;
			
			if (!_textures[id].loadFromFile(path))
			{
				std::cerr << "Failed to load texture: " << path << std::endl;
			}
			
			//_textures[id] = std::move(tempTexture);
		}
	}

	void ResourceManager::LoadAnimation(const YAML::Node& animationNode)
	{
		for (const YAML::Node& animation : animationNode)
		{
			std::string id = animation["id"].as<std::string>();
			std::string textureId = animation["textureId"].as<std::string>();
			std::vector<AnimationFrame> frames;

			std::cout << "Loading animation " << id << " with texture " << textureId << std::endl;

			for (const YAML::Node& frame : animation["frames"])
			{
				AnimationFrame frameData;
				frameData.texture = getTexture(textureId);
				frameData.textureRect = sf::IntRect(frame["x"].as<int>(), frame["y"].as<int>(), frame["width"].as<int>(), frame["height"].as<int>());
				frameData.duration = frame["duration"].as<float>();

				frames.push_back(frameData);
			}

		/*	if (!_animations[id].loadFromTexture(getTexture(textureId), frames))
			{
				std::cerr << "Failed to load animation: " << id << std::endl;
			}*/

			_animations[id] = std::move(frames);
		}
	}

	//sf::Sprite& ResourceManager::LoadSprite(const std::string id)
	//{
	//	_sprites[id] = sf::Sprite(_textures[id]);
	//}

	/*void ResourceManager::LoadShaders(const YAML::Node& shaderNode)
	{
		for (const YAML::Node& shader : shaderNode)
		{
			std::string name = shader["name"].as<std::string>();
			std::string path = shader["path"].as<std::string>();
			_resources["shaders"][name] = path;
		}
	}

	void ResourceManager::LoadModels(const YAML::Node& modelNode)
	{
		for (const YAML::Node& model : modelNode)
		{
			std::string name = model["name"].as<std::string>();
			std::string path = model["path"].as<std::string>();
			_resources["models"][name] = path;
		}
	}

	void ResourceManager::LoadMaterials(const YAML::Node& materialNode)
	{
		for (const YAML::Node& material : materialNode)
		{
			std::string name = material["name"].as<std::string>();
			std::string path = material["path"].as<std::string>();
			_resources["materials"][name] = path;
		}
	}

	void ResourceManager::LoadResources(const std::string path)
	{
		YAML::Node resources = YAML::LoadFile(path);

		LoadTextures(resources["textures"]);
		LoadShaders(resources["shaders"]);
		LoadModels(resources["models"]);
		LoadMaterials(resources["materials"]);
	}

	std::string ResourceManager::GetResourcePath(const std::string type, const std::string name)
	{
		return _resources[type][name].as<std::string>();
	}
}*/

}