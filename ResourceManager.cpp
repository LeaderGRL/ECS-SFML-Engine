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
		{
			LoadTextures(resource["textures"]);
		}
	}

	const sf::Texture& ResourceManager::getTexture(const std::string& id) const
	{
		//if (!_textures.contains(id))
		//{
		//	std::cerr << "Texture with id " << id << " does not exist" << std::endl;
		//}

		auto it = _textures.find(id);
		if (it != _textures.end()) {
			return it->second;
		}
		else {
			// Log error, and return a placeholder/fallback texture.
		}
		
		//return _textures.at(id);
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