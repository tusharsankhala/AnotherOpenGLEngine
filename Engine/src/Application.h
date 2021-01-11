#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window/Window.h"

#include "Event/ApplicationEvent.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate() {}

		virtual void OnEvent(Event& event);
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_window;
		bool m_running;
	};

	// To be defined in client.
	Application* CreateApplication();
}

#endif
