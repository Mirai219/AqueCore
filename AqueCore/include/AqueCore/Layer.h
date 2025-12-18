#pragma once

#include "AqueCore/Core.h"

#include <string>

namespace AQC
{
	class Event;
	class AQC_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer") : m_DebugName(debugName) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate() {}

		const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}
