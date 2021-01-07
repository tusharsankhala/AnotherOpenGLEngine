#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "../EnginePCH.h"

#include "Event.h"

namespace Engine
{
	class ENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y)
		{}

		inline float GetMouseX() const { return m_mouseX; }
		inline float GetMouseY() const { return m_mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_mouseX = 0, m_mouseY = 0;
	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float offsetX, float offsetY) : m_offsetX(offsetX), m_offsetY(offsetY)
		{}

		inline float GetOffsetX() const { return m_offsetX; }
		inline float GetOffsetY() const { return m_offsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled: " << m_offsetX << ", " << m_offsetY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_offsetX = 0, m_offsetY = 0;
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_button(button)
		{}

		int m_button;
	};


	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}
#endif