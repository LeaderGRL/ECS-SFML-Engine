#include "pch.h"
#include "LuaAPI.h"

namespace LeaderEngine 
{	
	LuaAPI::LuaAPI()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		luabridge::getGlobalNamespace(L)
			.beginClass<Entity>("Entity")
			.addConstructor<void(*) (void)>()
			.addFunction("GetId", &Entity::GetId)
			.addFunction("AddComponent", static_cast<void (Entity::*)(IComponent*)>(&Entity::AddComponent))
			.addFunction("SetPosition", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::setPosition))
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<EventManager>("EventManager")
			.addFunction("RegisterEvent", static_cast<void (EventManager::*)(INPUT_EVENT, luabridge::LuaRef)>(&EventManager::RegisterEvent))
			.addFunction("UnregisterEvent", &EventManager::UnregisterEvent)
			.addProperty("InvokeEvent", &EventManager::InvokeEvent)
			.endClass();
		
		luabridge::getGlobalNamespace(L)
			.beginClass<EntityManager>("EntityManager")
			.addFunction("CreateEntity", &EntityManager::CreateEntity)
			.addFunction("GetEntity", &EntityManager::GetEntity)
			.addStaticFunction("GetInstance", &EntityManager::GetInstance)
			.addFunction("test", &EntityManager::test)
			.endClass();
		
		luabridge::getGlobalNamespace(L)
			.beginClass<IComponent>("IComponent")
			.endClass()
			.deriveClass<IDrawableComponent, IComponent>("IDrawableComponent")
			.endClass()
			.deriveClass<Sprite2DComponent, IDrawableComponent>("Sprite2DComponent")
			.addConstructor<void(*) (void)>()
			.addFunction("SetSprite", &Sprite2DComponent::SetSprite)
			.addFunction("GetSprite", &Sprite2DComponent::GetSprite)
			.addFunction("SetSize", &Sprite2DComponent::SetSize)
			.addFunction("PlayAnimation", &Sprite2DComponent::PlayAnimation)
			.endClass()
			.deriveClass<ColliderComponent, IComponent>("ColliderComponent")
			.endClass()
			.deriveClass<BoxColliderComponent, ColliderComponent>("BoxColliderComponent")
			.addConstructor<void(*) (sf::Vector2f)>()
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<ResourceManager>("ResourceManager")
			.addStaticFunction("GetInstance", &ResourceManager::GetInstance)
			.addFunction("GetTexture", &ResourceManager::getTexture)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Texture>("Texture")
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Vector2f>("Vector2f")
			.addConstructor<void(*) (float, float)>()
			.addProperty("x", &sf::Vector2f::x)
			.addProperty("y", &sf::Vector2f::y)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Sprite>("Sprite")
			.addConstructor<void(*) (void)>()
			.addFunction("setPosition", static_cast<void (sf::Sprite::*)(float, float)>(&sf::Sprite::setPosition))
			.addFunction("setColor", &sf::Sprite::setColor)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("LeaderEngine")
			.beginClass<INPUT_EVENT>("INPUT_EVENT")
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("LeaderEngine")
			.addVariable("INPUT_EVENT_KEY_PRESSED", INPUT_EVENT::KeyPressed, false)
			.endNamespace();
			

		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Event>("Event")
			.addConstructor<void(*) (void)>()
			.addFunction("type", &sf::Event::type)
		
		luabridge::getGlobalNamespace(L)
			.beginClass<sf::Event>("Event")
			.endClass();


		//EntityManager globalEntityManager = EntityManager::GetInstance();
		//luabridge::setGlobal(L, &Entity, "Entity");
		//luabridge::setGlobal(L, &EntityManager::GetInstance(), "EntityManager");

		int scriptLoadStatus = luaL_dofile(L, "../LeaderEngine/Script.lua"); // Load the script
		report_errors(L, scriptLoadStatus);
		//globalEntityManager["Instance"] = &EntityManager::GetInstance();
	}

	LuaAPI::~LuaAPI()
	{
		lua_close(L);
	}

	void LuaAPI::LoadScript(const char* path)
	{
		luaL_dofile(L, path);
	}

	//void CPP_To_Lua::CallFunction(const char* funcName)
	//{
	//	lua_getglobal(L, funcName);
	//	lua_pcall(L, 0, 0, 0);
	//}

	void LuaAPI::report_errors(lua_State* luaState, int status)
	{
		if (status == 0) {
			return;
		}

		std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(luaState, 1);
	}
}
