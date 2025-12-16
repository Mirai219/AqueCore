#pragma once

#include "Event.h"
#include "AqueCore/KeyCodes.h"

namespace AQC {

	class AQC_API KeyEvent : public Event {

	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(KeyCode keycode) : m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	class AQC_API KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeated)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class AQC_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class AQC_API KeyTypedEvent : public Event {
	public:
		KeyTypedEvent(uint32_t codepoint)
			: m_Codepoint(codepoint) {}

		uint32_t GetCodepoint() const { return m_Codepoint; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << (char)m_Codepoint;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	private:
		uint32_t m_Codepoint;
	};
}