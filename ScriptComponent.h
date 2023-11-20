#pragma once
#include "LuaAPI.h"
#include <string>

#include "IComponent.h"


namespace LeaderEngine
{
	class ScriptComponent : public IComponent
	{
		private:
			std::string _scriptName;
			void report_errors(lua_State* luaState, int status);

		public :
			ScriptComponent();
			ScriptComponent(const char* path);

			void Update(float deltaTime) override;
			void LoadScript(const char* path);
			COMPONENT_TYPE GetType() const override;

	};
}

