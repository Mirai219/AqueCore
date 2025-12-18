#pragma once

#include "AqueCore/Core.h"
#include <spdlog/spdlog.h>
#include <memory>

namespace AQC
{
	class AQC_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define AQC_CORE_ERROR(...)	::AQC::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AQC_CORE_WARN(...)	::AQC::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AQC_CORE_INFO(...)	::AQC::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AQC_CORE_TRACE(...)	::AQC::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define AQC_ERROR(...)		::AQC::Log::GetClientLogger()->error(__VA_ARGS__)
#define AQC_WARN(...)		::AQC::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AQC_INFO(...)		::AQC::Log::GetClientLogger()->info(__VA_ARGS__)
#define AQC_TRACE(...)		::AQC::Log::GetClientLogger()->trace(__VA_ARGS__)

#ifdef AQC_ENABLE_ASSERTS
#define AQC_CORE_ASSERT(x, ...) \
			{ \
				if(!(x)) { \
					::AQC::Log::GetCoreLogger()->error("Assertion Failed: {0}", __VA_ARGS__); \
					__debugbreak(); \
				} \
			}
#define	AQC_ASSERT(x, ...) \
			{ \
				if(!(x)) { \
					::AQC::Log::GetClientLogger()->error("Assertion Failed: {0}", __VA_ARGS__); \
					__debugbreak(); \
				} \
			}
#else
#define AQC_CORE_ASSERT(x, ...) {}
#define	AQC_ASSERT(x, ...) {}
#endif