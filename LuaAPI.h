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
			void LoadScript(const char* path);
		
	};
}
