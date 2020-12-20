#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

namespace RenderEngine
{
	class RENDERENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client.
	Application* CreateApplication();
}

#endif
