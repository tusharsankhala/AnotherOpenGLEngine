#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef ENGINE_PLATFORM_WINDOWS

#include "Log/Log.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGINE_CORE_WARN("Engine Logger Initialized");
	ENGINE_CORE_INFO("App Logger Initialized");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#endif

#endif
