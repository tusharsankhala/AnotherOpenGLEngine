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

#define BIT(x) (1 << x)

#endif
