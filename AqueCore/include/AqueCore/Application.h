	#pragma once

	#include "AqueCore/Core.h"

	namespace AQC
	{
		class AQC_API Application
		{
		public:
			Application();
			virtual ~Application();

			virtual void Run();

			inline static Application& Get() { return *s_Instance; }

		private:
			bool m_Running = true;

			static Application* s_Instance;
		};

		// To be defined in CLIENT
		Application* CreateApplication();
	}