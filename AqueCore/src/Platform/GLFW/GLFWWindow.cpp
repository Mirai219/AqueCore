#include "Platform/GLFW/GLFWWindow.h"
#include "AqueCore/Log.h"
#include "AqueCore/Events/Event.h"
#include "AqueCore/Events/ApplicationEvent.h"
#include "AqueCore/Events/KeyEvent.h"
#include "AqueCore/Events/MouseEvent.h"
#include "Platform/GLFW/GLFWKeyMap.h"
#include "Platform/GLFW/GLFWMouseMap.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AQC
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		AQC_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new GLFWWindow(props);
	}

	GLFWWindow::GLFWWindow(const WindowProps& props)
	{
		Init(props);
	}

	GLFWWindow::~GLFWWindow()
	{
		ShutDown();
	}

	void GLFWWindow::OnUpdate()
	{

	}

	void GLFWWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void GLFWWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	bool GLFWWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void GLFWWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	void GLFWWindow::SetEventCallback(const EventCallbackFn callback)
	{
		m_Data.EventCallback = callback;
	}

	void* GLFWWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	void GLFWWindow::Init(const WindowProps& props)
	{
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		m_Data.Title = props.Title;

		AQC_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			AQC_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = w;
				data.Height = h;
				if (data.EventCallback) {
					WindowResizeEvent e(w, h);

					data.EventCallback(e);
				}
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (data.EventCallback) {
					WindowCloseEvent e;
					data.EventCallback(e);
				}
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int modes)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (data.EventCallback) {
					switch (action)
					{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(GLFWKeyToAqureKey(key), 0);
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(GLFWKeyToAqureKey(key));
						data.EventCallback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent e(GLFWKeyToAqureKey(key), 1);
						data.EventCallback(e);
						break;
					}
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent e(codepoint);
				data.EventCallback(e);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int modes)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (data.EventCallback) {
					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(GLFWMouseButtonToAqure(button));
						data.EventCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(GLFWMouseButtonToAqure(button));
						data.EventCallback(e);
						break;
					}
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x_off, double y_off)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (data.EventCallback) {
					MouseScrolledEvent e((float)x_off, (float)y_off);
					data.EventCallback(e);
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				if (data.EventCallback) {
					MouseMovedEvent e((float)xPos, (float)yPos);
					data.EventCallback(e);
				}
			});
	}

	void GLFWWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
}