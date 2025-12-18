#pragma once

#include "AqueCore/Core.h"
#include "AqueCore/Window.h"
#include "AqueCore/LayerStack.h"

namespace AQC
{
	class Event;
	class WindowCloseEvent;

	class AQC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);

		inline static Application& Get() { return *s_Instance; }

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool m_Running = true;
		Window* m_Window;
		static Application* s_Instance;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}