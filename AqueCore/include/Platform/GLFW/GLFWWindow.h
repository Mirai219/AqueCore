#pragma once

#include "AqueCore/Core.h"
#include "AqueCore/Window.h"

class GLFWwindow;

namespace AQC
{
	class AQC_API GLFWWindow : public Window
	{
	public:
		GLFWWindow(const WindowProps& props);
		virtual ~GLFWWindow();

		virtual void OnUpdate() override;

		void PollEvents() override;
		void SwapBuffers() override;

		bool IsVSync() const override;
		void SetVSync(bool enabled) override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn callback) override;

		void* GetNativeWindow() const override;

	private:
		void Init(const WindowProps& props) override;
		void ShutDown() override;

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string	Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}