#pragma once

#include "AqueCore/Core.h"
#include "AqueCore/Layer.h"

namespace AQC
{
	class AQC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}