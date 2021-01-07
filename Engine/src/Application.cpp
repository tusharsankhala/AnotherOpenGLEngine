#include "EnginePCH.h"

#include "Application.h"
#include "Event/ApplicationEvent.h"
#include "Log/Log.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	Application::Application()
	{
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}

	Application* CreateApplication();
}