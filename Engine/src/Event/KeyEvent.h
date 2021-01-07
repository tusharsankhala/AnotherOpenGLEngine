#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "../EnginePCH.h"

#include "Event.h"

namespace Engine
{
	class ENGINE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyEvent() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) : m_keyCode(keyCode)
		{}

		int m_keyCode;
	};

	class ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
		
	private:
		int m_repeatCount;
	};

	class ENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), m_repeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	private:
		int m_repeatCount;
	};

}

#endif