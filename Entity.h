#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "IComponent.h"


//extern "C"
//{
//	#include "lua.h"
//	#include "lualib.h"
//	#include "lauxlib.h"
//}

#include "lua.hpp"
#include "luabridge3/LuaBridge/LuaBridge.h"


namespace LeaderEngine {
	class Entity : public sf::Drawable, public sf::Transformable
	{
		private :
			Entity* _parent = nullptr;  // Pointer to the parent entity
			std::unordered_map<std::string, std::unique_ptr<Entity>> _children; // Child entities

		protected :
			int _id;
			std::vector<std::shared_ptr<IComponent>> _components;
		public:
			void report_errors(lua_State* luaState, int status);
			Entity();
			~Entity();
			Entity(std::string name);
			Entity(const Entity&) = delete; // delete copy constructor
			Entity& operator=(const Entity&) = delete; // delete copy assignment
			Entity(Entity&&) = default; // use default move constructor
			Entity& operator=(Entity&&) = default; // use default move assignment
			//sf::Packet& operator<<(sf::Packet& packet, const Entity& entity); // Overload the << operator to send an entity through the network
			//sf::Packet& operator>>(sf::Packet& packet, Entity& entity); // Overload the >> operator to receive an entity through the network
			
			int GetId() const;
			void SetId(int id);
			void SetParent(Entity* parent);
			Entity* GetParent() const;
			Entity* AddChild(const std::string& name);
			Entity* GetChild(const std::string& name);
			std::unordered_map<std::string, std::unique_ptr<Entity>>& GetChildren();
			void RemoveChild(const std::string& name);

			void Update(float deltaTime) const; // Update through all the components
			void Start();
			void Destroy();
			void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Walk through all the rendable components
			//void AddComponent(IComponent* component);
			void AddComponent(int type);
			luabridge::LuaRef GetComponent(int type);

			std::vector<std::shared_ptr<IComponent>>& GetComponents();

			template<typename T, typename ...Args> 
			void AddComponent(Args&&... args) // r value reference on n arguments
			{
				static_assert(std::is_base_of_v<IComponent, T>, "T must inherit from IComponent"); // Check if T inherit from IComponent
				_components.push_back(std::make_shared<T>(std::forward<Args>(args)...)); // forwards the arguments args to the constructor of T with their original value
			}
			
			template<typename T>
			T* GetComponent() const
			{
				for (const auto& comp : _components)
				{
					if (dynamic_cast<T*>(comp.get()))
						return static_cast<T*>(comp.get());
				}
				return nullptr;
			}
	};
}