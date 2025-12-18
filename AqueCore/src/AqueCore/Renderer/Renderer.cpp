#include "AqueCore/Renderer/Renderer.h"
#include "AqueCore/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace AQC
{
	std::unique_ptr<RendererAPI> Renderer::s_RendererAPI;

	void Renderer::Init()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			s_RendererAPI = std::make_unique<OpenGLRendererAPI>();
			break;
		default:
			return;
		}

		s_RendererAPI->Init();
	}

	void Renderer::BeginFrame()
	{

	}

	void Renderer::EndFrame()
	{
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		s_RendererAPI->SetClearColor(r, g, b, a);
	}

	void Renderer::Clear()
	{
		s_RendererAPI->Clear();
	}
}
