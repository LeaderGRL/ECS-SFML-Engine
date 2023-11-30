#include "pch.h"
#include "ScriptComponent.h"


namespace LeaderEngine
{
	//ScriptComponent::ScriptComponent()
	//{

	//}

	ScriptComponent::ScriptComponent(const char* path) : _luaObject(luabridge::LuaRef::fromStack(LuaAPI::GetInstance().GetLuaState(), -1))
	{
		LoadScript(path);
	}

	void ScriptComponent::Update(int deltaTime)
	{
		if (!_luaObject.isTable())
		{
			return;
		}

		const luabridge::LuaRef& update = _luaObject["Update"];
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
		const int loadScriptStatus = luaL_dofile(LuaAPI::GetInstance().GetLuaState(), path);
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

