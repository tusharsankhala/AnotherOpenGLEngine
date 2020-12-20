#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#ifdef RENDERENGINE_PLATFORM_WINDOWS

extern RenderEngine::Application* RenderEngine::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Render  Engine has Started" << '\n';
	auto app = RenderEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif

#endif
