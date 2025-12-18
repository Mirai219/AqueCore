#pragma once
#pragma once

#include "AqueCore/Renderer/RendererAPI.h"

namespace AQC
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(int x, int y, int width, int height) override;
		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void Clear() override;
	};
}
