#pragma once

#include "AqueCore/Core.h"
#include <string>
#include <functional>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/fmt.h>

namespace AQC
{
	enum class EventType
	{
		None = 0,
		WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
	};

	enum EventCategory
	{
		None						= 0,
		EventCategoryApplication	= BIT(1),
		EventCategoryInput			= BIT(2),
		EventCategoryKeyboard		= BIT(3),
		EventCategoryMouse			= BIT(4),
		EventCategoryMouseButton	= BIT(4),
	};

	#define EVENT_CLASS_TYPE(type) \
		static EventType GetStaticType() { return EventType::type; } \
		virtual EventType GetEventType() const override { return GetStaticType(); } \
		virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class AQC_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }
		virtual ~Event() = default;

		inline bool HasHanled() { return m_Handled; }

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

template<typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<AQC::Event, T>, char>> 
	: fmt::formatter<std::string>
{
	auto format(const AQC::Event& e, format_context& ctx) const
	{
		return fmt::formatter<std::string>::format(e.ToString(), ctx);
	}
};