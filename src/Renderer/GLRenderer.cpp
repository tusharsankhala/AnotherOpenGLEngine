#include "GLRenderer.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool GLRenderer::InitializeRenderer()
{
	InitializeBuffer();
	LoadAndCompileShader("E:\\GitReposMy\\AnotherOpenGLEngine\\src\\Shaders\\PassThruVert.vert",
		"E:\\GitReposMy\\AnotherOpenGLEngine\\src\\Shaders\\PassThruFrag.frag");

	return true;
}

bool GLRenderer::InitializeBuffer()
{
	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f, 1.0f, 0.0f
	};

	// Vertex Array Object.
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

		// Vertex Buffer Object.
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	return true;
}

std::string LoadShaderFile(const std::string fileName)
{
	std::ifstream shaderFile;
	std::string temp = "";
	std::string src = "";


	shaderFile.open(fileName.c_str());
	if (shaderFile.is_open())
	{
		while (std::getline(shaderFile, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cerr << "Error Opening File" << "\n";
	}

	if (shaderFile.is_open())
		shaderFile.close();

	return src;
}

static unsigned int CompileShader(unsigned int shaderType, const std::string& source)
{
	unsigned int shaderID = glCreateShader(shaderType);
	const char* src = source.c_str();

	glShaderSource(shaderID, 1, &src, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

		char* strInfoLog = new char[length + 1];
		glGetShaderInfoLog(shaderID, length, &length, strInfoLog);

		std::cerr << "Compilation Error in shader: " << strInfoLog << "\n";

		delete[] strInfoLog;
	}

	return shaderID;

}

unsigned int GLRenderer::LoadAndCompileShader(const std::string vertShaderFileName, const std::string fragShaderFileName)
{
	unsigned int vertShader, fragShader;

	// vert/fragment shader will be non zero if succefully created
	std::string vertShaderCode = LoadShaderFile(vertShaderFileName);
	std::string fragShaderCode = LoadShaderFile(fragShaderFileName);

	m_programID = glCreateProgram();
	vertShader = CompileShader(GL_VERTEX_SHADER, vertShaderCode);
	fragShader = CompileShader(GL_FRAGMENT_SHADER, fragShaderCode);

	// Attaching shader.
	glAttachShader(m_programID, vertShader);
	glAttachShader(m_programID, fragShader);

	int result = 0;
	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
	}


	glValidateProgram(m_programID);
	glGetProgramiv(m_programID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
	}

	uniformModel = glGetUniformLocation(m_programID, "model");

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return 0;
}

bool GLRenderer::InitializeShaders()
{
	return false;
}

void GLRenderer::RenderFrame()
{
	
}