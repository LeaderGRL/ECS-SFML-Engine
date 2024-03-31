#include "pch.h"
#include "ScriptComponent.h"


namespace LeaderEngine
{
	ScriptComponent::ScriptComponent() : _luaObject(luabridge::LuaRef::fromStack(LuaAPI::GetInstance().GetLuaState(), -1))
	{
		/*if (!_luaObject.isTable())
		{
			return;
		}

		const luabridge::LuaRef& init = _luaObject["Init"];
		if (!init.isFunction())
		{
			return;
		}


		if (const luabridge::LuaResult res = init(_luaObject); !res.wasOk())
			std::cout << "Error : " << res.errorCode() << " : " << res.errorMessage() << std::endl;

		_luaObject = luabridge::LuaRef::fromStack(LuaAPI::GetInstance().GetLuaState(), -1);*/

	}

	ScriptComponent::ScriptComponent(const char* path) : _luaObject(luabridge::LuaRef::fromStack(LuaAPI::GetInstance().GetLuaState(), -1))
	{
		LoadScript(path);

		_luaObject = luabridge::LuaRef::fromStack(LuaAPI::GetInstance().GetLuaState(), -1);
	}

	void ScriptComponent::Init()
	{
		std::cout << "ScriptComponent Init" << std::endl;
		if (!_luaObject.isTable()) // if the lua object is not a table, return
		{
			return;
		}

		const luabridge::LuaRef& init = _luaObject["Init"]; // get the init function from the lua object
		if (!init.isFunction())
		{
			return;
		}

		// In lua, a function set like Object:Function is actually Object.Function(Object)
		// So we need to pass the object as the first parameter
		if (const luabridge::LuaResult res = init(_luaObject); !res.wasOk()) // init statement
			std::cout << "Error : " << res.errorCode() << " : " << res.errorMessage() << std::endl;	
	}

	void ScriptComponent::Update(float deltaTime)
	{
		if (!_luaObject.isTable()) // if the lua object is not a table, return
		{
			return;
		}

		const luabridge::LuaRef& update = _luaObject["Update"]; // get the update function from the lua object
		if (!update.isFunction())
		{
			return;
		}

		// In lua, a function set like Object:Function is actually Object.Function(Object)
		// So we need to pass the object as the first parameter
		if (const luabridge::LuaResult res = update(_luaObject, deltaTime); !res.wasOk()) // init statement
			std::cout << "Error : " << res.errorCode() << " : " << res.errorMessage() << std::endl;

	}

	void ScriptComponent::LoadScript(const char* path)
	{
		const int loadScriptStatus = luaL_dofile(LuaAPI::GetInstance().GetLuaState(), path); // Load the script
		report_errors(LuaAPI::GetInstance().GetLuaState(), loadScriptStatus);
	}

	COMPONENT_TYPE ScriptComponent::GetType() const
	{
		return COMPONENT_TYPE::SCRIPT;
	}

	void ScriptComponent::report_errors(lua_State* luaState, int status)
	{
		if (status == 0) {
			return;
		}

		std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

		// remove error message from Lua state
		lua_pop(luaState, 1);
	}

}

