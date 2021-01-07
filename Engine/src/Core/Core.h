#ifndef CORE_H
#define CORE_H

#ifdef ENGINE_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Render Engine only Supports windows
#endif

#ifdef ENGINE_ENABLE_ASSERTS
	#define ENGINE_ASSERTS(x, ...) {if(!(x)) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugBreak(); } }
	#define ENGINE_CORE_ASSERTS(x, ...) {if(!(x)) { ENGINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugBreak(); } }
#else
	#define ENGINE_ASSERT(x, ...)
	#define ENGINE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#endif