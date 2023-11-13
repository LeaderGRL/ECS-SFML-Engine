#pragma once

#include <iostream>
#include "lua.hpp"
#include "luabridge3/LuaBridge/LuaBridge.h"
#include "Entity.h"
#include "EntityManager.h"
#include "BoxColliderComponent.h"
#include "EventManager.h"
#include "Utils.h"

namespace LeaderEngine
{
	class LuaAPI
	{
		private:
			lua_State* L;
			void report_errors(lua_State* luaState, int status);
			
		public:
			LuaAPI();
			~LuaAPI();
			LuaAPI(LuaAPI const&) = delete;
			LuaAPI(LuaAPI&&) = delete;
			LuaAPI& operator=(LuaAPI const&) = delete;
			LuaAPI& operator=(LuaAPI&&) = delete;
			static LuaAPI& GetInstance();

			void CPP_To_LUA();
			void LoadScript(const char* path);
			void GetLuaStack();
			lua_State* GetLuaState();
			//void RegisterEvent(int inputEvent, const luabridge::LuaRef& callback);
			static bool Call_Errors(lua_State* luaState, const luabridge::LuaRef& func, int nbArgs, int nbReturnValue);
			void CallFunction(const std::string& funcName);
		
	};
}
