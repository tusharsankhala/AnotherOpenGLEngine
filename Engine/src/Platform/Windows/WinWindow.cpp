#include "EnginePCH.h"
#include "../../Core/Core.h"
#include "../../Log/Log.h"
#include "WinWindow.h"

namespace Engine
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WinWindow(props);
	}

	WinWindow::WinWindow(const WindowProps& props)
	{
		Init(props);
	}

	WinWindow::~WinWindow()
	{
		ShutDown();
	}

	void WinWindow::Init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		ENGINE_CORE_INFO("Creating window {0} ({1} {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);
	}

	void WinWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	}

	void WinWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WinWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enabled;
	}

	bool WinWindow::IsVSync() const
	{
		return m_data.VSync;
	}
}