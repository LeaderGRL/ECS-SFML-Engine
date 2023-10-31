#include "pch.h"
#include "CPP_To_Lua.h"

namespace LeaderEngine 
{	
	CPP_To_Lua::CPP_To_Lua()
	{
		L = luaL_newstate();
		luaL_openlibs(L);

		luabridge::getGlobalNamespace(L)
			.beginClass<Entity>("Entity")
			.addConstructor<void(*) (void)>()
			.addFunction("GetId", &Entity::GetId)
			.addFunction("PrintNumber", &Entity::PrintNumber)
			.endClass();

		luabridge::getGlobalNamespace(L)
			.beginClass<EntityManager>("EntityManager")
			.addConstructor<void(*) (void)>()
			.addFunction("CreateEntity", &EntityManager::CreateEntity)
			.addFunction("GetEntity", &EntityManager::GetEntity)
			.endClass();

		//EntityManager globalEntityManager = EntityManager::GetInstance();
		//luabridge::setGlobal(L, &Entity, "Entity");
		luabridge::setGlobal(L, &EntityManager::GetInstance(), "EntityManager");

		int scriptLoadStatus = luaL_dofile(L, "../LeaderEngine/Script.lua"); // Load the script
		report_errors(L, scriptLoadStatus);
		//globalEntityManager["Instance"] = &EntityManager::GetInstance();
	}

	CPP_To_Lua::~CPP_To_Lua()
	{
		lua_close(L);
	}

	//void CPP_To_Lua::LoadScript(const char* path)
	//{
	//	luaL_dofile(L, path);
	//}

	//void CPP_To_Lua::CallFunction(const char* funcName)
	//{
	//	lua_getglobal(L, funcName);
	//	lua_pcall(L, 0, 0, 0);
	//}

	void CPP_To_Lua::report_errors(lua_State* luaState, int status)
	{
		if (status == 0) {
			return;
		}

		std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(luaState, 1);
	}
}
