#pragma once

#ifdef AQC_PLATFORM_WINDOWS
#ifdef AQC_BUILD_DLL
#define AQC_API __declspec(dllexport)
#else 
#define AQC_API __declspec(dllimport)
#endif
#else
#error AqueCore only supports Windows
#endif

#define BIT(x)	1 << x

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)