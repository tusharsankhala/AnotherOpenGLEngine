#ifndef WINDOW_H
#define WINDOW_H

#include "../Core/Core.h"
#include "../Event/Event.h"

namespace Engine
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& _title = "OpenGL Engine",
					const unsigned int _width = 1280, const unsigned int _height = 720)
			: title(_title), width(_width), height(_height)
		{}
	};

	// Interface representing a desktop system based window.
	class ENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window Attributes.
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}

#endif