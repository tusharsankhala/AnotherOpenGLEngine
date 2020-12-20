#ifndef CORE_H
#define CORE_H

#ifdef RENDERENGINE_PLATFORM_WINDOWS
	#ifdef RENDERENGINE_BUILD_DLL
		#define RENDERENGINE_API __declspec(dllexport)
	#else
		#define RENDERENGINE_API __declspec(dllimport)
	#endif
#else
	#error Render Engine only Supports windows
#endif

#endif
