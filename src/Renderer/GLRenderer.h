#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <string>

#include <GL/glew.h>
#include <GL/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GLRenderer
{
public:
	bool InitializeRenderer();
	bool InitializeBuffer();
	unsigned int LoadAndCompileShader(const std::string vertShaderFileName, const std::string fragShaderFileName);
	bool InitializeShaders();

	void RenderFrame();

	// Shader Program.
	unsigned int m_programID;
	unsigned int m_VAO;
	unsigned int uniformModel;
	bool direction = true;
	float directionIncrement = 0.0001f;

private:

	unsigned int m_VBO;
	unsigned int m_shader;
	
};

#endif
