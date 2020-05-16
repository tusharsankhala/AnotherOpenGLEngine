#ifndef SHADER_H
#define SHADER_H

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	bool LoadShaderFromFile(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath);
	unsigned int CompileShaderSource(const char* vertShaderCode, GLenum shaderType);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetProgramID();

	void UseShader();
	void ClearShader();

private:
	GLuint m_programID, m_uniformProjection, m_uniformModel;
};

#endif
