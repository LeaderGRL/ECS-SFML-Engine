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
			.addFunction("Move", static_cast<void (sf::Transformable::*)(float, float)>(&sf::Transformable::move))
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<EventManager>("EventManager")
			.addStaticFunction("GetInstance", &EventManager::GetInstance)
			.addFunction("RegisterEvent", static_cast<void (EventManager::*)(int, const luabridge::LuaRef&)>(&EventManager::RegisterEvent))
			.addFunction("UnregisterEvent", &EventManager::UnregisterEvent)
			.addFunction("InvokeEvent", &EventManager::InvokeEvent)
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
			.addVariable("INPUT_EVENT_KEY_PRESSED", INPUT_EVENT::KeyPressed)
			.addVariable("INPUT_EVENT_KEY_RELEASED", INPUT_EVENT::KeyReleased)
			.endNamespace();

		//luabridge::getGlobalNamespace(L)
		//	.beginNamespace("sf")
		//	.beginClass<sf::Event>("Event")
		//	.addConstructor<void(*) (void)>()
		//	.addProperty("type", &sf::Event::type)
		//	.addProperty("key", &sf::Event::key)
		//	.endClass()
		//	.deriveClass<sf::Event::KeyEvent, sf::Event>("KeyEvent")
		//	.addProperty("code", &sf::Event::KeyEvent::code)
		//	.endClass();
		//	

		//luabridge::getGlobalNamespace(L)
		//	.beginNamespace("sf")
		//	.beginClass<sf::Event::KeyEvent>("KeyEvent")
		//	.addProperty("code", &sf::Event::KeyEvent::code)
		//	.endClass()
		//	.beginClass<sf::Event>("Event")
		//	.addConstructor<void(*) (void)>()
		//	.addProperty("type", &sf::Event::type)
		//	.addProperty("key", &sf::Event::key)
		//	.endClass();


		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Event>("Event")
			.addConstructor<void(*) (void)>()
			.addProperty("type", &sf::Event::type)
			//.addProperty("KeyPressed", sf::Event::KeyPressed)
			.addProperty("key", &sf::Event::key)
			.endClass();
		

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.addVariable("Closed", sf::Event::EventType::Closed)
			.addVariable("KeyPressed", sf::Event::EventType::KeyPressed)
			.addVariable("KeyReleased", sf::Event::EventType::KeyReleased)
			.endNamespace();

		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Keyboard::Key>("Key")
			.endClass()
			.addVariable("KEY_A", sf::Keyboard::Key::A)
			.addVariable("KEY_B", sf::Keyboard::Key::B)
			.addVariable("KEY_C", sf::Keyboard::Key::C)
			.addVariable("KEY_D", sf::Keyboard::Key::D)
			.addVariable("KEY_E", sf::Keyboard::Key::E)
			.addVariable("KEY_F", sf::Keyboard::Key::F)
			.addVariable("KEY_G", sf::Keyboard::Key::G)
			.addVariable("KEY_H", sf::Keyboard::Key::H)
			.addVariable("KEY_I", sf::Keyboard::Key::I)
			.addVariable("KEY_J", sf::Keyboard::Key::J)
			.addVariable("KEY_K", sf::Keyboard::Key::K)
			.addVariable("KEY_L", sf::Keyboard::Key::L)
			.addVariable("KEY_M", sf::Keyboard::Key::M)
			.addVariable("KEY_N", sf::Keyboard::Key::N)
			.addVariable("KEY_O", sf::Keyboard::Key::O)
			.addVariable("KEY_P", sf::Keyboard::Key::P)
			.addVariable("KEY_Q", sf::Keyboard::Key::Q)
			.addVariable("KEY_R", sf::Keyboard::Key::R)
			.addVariable("KEY_S", sf::Keyboard::Key::S)
			.addVariable("KEY_T", sf::Keyboard::Key::T)
			.addVariable("KEY_U", sf::Keyboard::Key::U)
			.addVariable("KEY_V", sf::Keyboard::Key::V)
			.addVariable("KEY_W", sf::Keyboard::Key::W)
			.addVariable("KEY_X", sf::Keyboard::Key::X)
			.addVariable("KEY_Y", sf::Keyboard::Key::Y)
			.addVariable("KEY_Z", sf::Keyboard::Key::Z)
			.endNamespace();
		
		luabridge::getGlobalNamespace(L)
			.beginNamespace("sf")
			.beginClass<sf::Event::KeyEvent>("KeyEvent")
			.addStaticFunction("GetKeyEventCode", &Utils::GetKeyEventCode)
			//.addProperty("code", static_cast<int>(&sf::Event::KeyEvent::code), false)
			.endClass();
		
		int scriptLoadStatus = luaL_dofile(L, "../LeaderEngine/Script.lua"); // Load the script
		report_errors(L, scriptLoadStatus);

		//EventManager::GetInstance().
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
	
	bool LuaAPI::Call_Errors(lua_State* luaState, const luabridge::LuaRef& func, int nbArgs, int nbReturnValue)
	{
		if (!func.isFunction())
			return false;

		func.push(); // Push the Lua function onto the stack

		if (lua_pcall(luaState, nbArgs, nbReturnValue, 0) != 0) // Call the function
		{
			std::cerr << "Lua error: " << lua_tostring(func.state(), -1) << std::endl;
			lua_pop(func.state(), 1);  // pop the error message from the stack
			return false;
		}

		return true;
	}
}
