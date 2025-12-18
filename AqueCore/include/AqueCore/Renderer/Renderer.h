#pragma once

#include <memory>
#include "AqueCore/Renderer/RendererAPI.h"

namespace AQC
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginFrame();
		static void EndFrame();

		static void SetClearColor(float r, float g, float b, float a);
		static void Clear();

	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};
}
