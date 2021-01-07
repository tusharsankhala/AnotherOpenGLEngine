#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window/Window.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running;
	};

	// To be defined in client.
	Application* CreateApplication();
}

#endif
