#pragma once
namespace LeaderEngine {
	class AComponent
	{
		protected :
			int _id;
		public : 
			AComponent();
			~AComponent();
			virtual void Update() = 0;
			virtual void Start() = 0;
			virtual void Destroy() = 0;
			int GetId();
			void SetId(int id);
	};
}

