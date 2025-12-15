#include "AqueCore/Application.h"
#include "stdio.h"

namespace AQC
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			
		}
	}
}