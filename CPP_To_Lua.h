#pragma once

#include <iostream>
#include "lua.hpp"
#include "luabridge3/LuaBridge/LuaBridge.h"
#include "Entity.h"
#include "EntityManager.h"

namespace LeaderEngine
{
	class CPP_To_Lua
	{
		private:
			 
			lua_State* L;
			void report_errors(lua_State* luaState, int status);
		public:
			CPP_To_Lua();
			~CPP_To_Lua();
			
			 
	};
}
