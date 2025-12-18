#pragma once

#include "AqueCore/Core.h"

#include <string>
#include <functional>

namespace AQC
{
	class Event;

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "AqueCore Engine", unsigned int width = 1280, unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class AQC_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		static Window* Create(const WindowProps& prop = WindowProps());
		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool enabled) = 0;

		virtual void SetEventCallback(const EventCallbackFn callback) = 0;

		virtual void* GetNativeWindow() const = 0;

	private:
		virtual void Init(const WindowProps& props) = 0;
		virtual void ShutDown() = 0;
	};
}