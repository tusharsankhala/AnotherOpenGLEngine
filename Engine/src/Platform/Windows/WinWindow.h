#ifndef WINWINDOWS_H
#define WINWINDOWS_H

#include "../../Window/Window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	class WinWindow : public Window
	{
	public:
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_data.width; }
		inline unsigned int GetHeight() const override { return m_data.height; }

		// Window Attributes.
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn EventCallback;

		};

		WindowData m_data;
	};
}

#endif