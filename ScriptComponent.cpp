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

	void ScriptComponent::Update(float deltaTime)
	{
		//luabridge::LuaRef update = luabridge::getGlobal(LuaAPI::GetInstance().GetLuaState(), "Update"); // get update function
		//luabridge::LuaResult res = update(deltaTime); // Call update function

		if (_luaObject.isTable())
		{
			luabridge::LuaRef update = _luaObject["Update"];
			if (update.isFunction())
				//std::cout << "iiiiiiiiiiii" << std::endl;
				luabridge::LuaResult res = update(deltaTime);
		} 
		else
		{
			//std::cout << "ttttttttt" << std::endl;
		}
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

