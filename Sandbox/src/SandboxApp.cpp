#include <RenderEngine.h>

class SandBox : public RenderEngine::Application
{
public:
	SandBox() {}
	~SandBox() {}
};

RenderEngine::Application* RenderEngine::CreateApplication()
{
	return new SandBox();
}