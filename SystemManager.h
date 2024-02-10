#pragma once

namespace  LeaderEngine 
{
	class SystemManager
	{
		public:
			static SystemManager& GetInstance();

			SystemManager();
			~SystemManager();

			void Initialize();
			void Update();
			void Shutdown();
	};
}

