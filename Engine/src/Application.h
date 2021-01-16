#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"
#include "Event/ApplicationEvent.h"

namespace Engine
{
	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	// To be defined in client.
	Application* CreateApplication();
}

#endif
