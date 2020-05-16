#include "Shader.h"

#include <vector>

Shader::Shader() : m_programID(0), m_uniformProjection(0), m_uniformModel(0)
{}

bool Shader::LoadShaderFromFile(const std::string& vertShaderFilePath, const std::string& fragShaderFilePath)
{
	// Reading Vertex shader file.
	std::fstream vertShaderFile(vertShaderFilePath.c_str(), std::ios::in);

	if (!vertShaderFile.is_open())
	{
		std::cerr << "Error opening vertex shader file: " << vertShaderFilePath << "\n";
		vertShaderFile.close();
		return false;
	}

	std::string line;
	std::string shaderSource;
	while (!vertShaderFile.eof())
	{
		std::getline(vertShaderFile, line);
		shaderSource.append(line + "\r\n");
	}
	
	unsigned int vertShaderID = CompileShaderSource(shaderSource.c_str(), GL_VERTEX_SHADER);
	if (vertShaderID < 0)
	{
		return false;
	}

	// Reading fragment shader file.
	std::fstream fragShaderFile(fragShaderFilePath.c_str(), std::ios::in);
	if (!fragShaderFile.is_open())
	{
		std::cerr << "Error opening fragment shader file: " << fragShaderFilePath << "\n";
		fragShaderFile.close();
		return false;
	}

	line.clear();
	shaderSource.clear();
	while (!fragShaderFile.eof())
	{
		std::getline(fragShaderFile, line);
		shaderSource.append(line + "\r\n");
	}

	unsigned int fragShaderID = CompileShaderSource(shaderSource.c_str(), GL_FRAGMENT_SHADER);
	if (fragShaderID < 0)
	{
		return false;
	}

	m_programID = glCreateProgram();
	if (!m_programID)
	{
		std::cerr << "Error creating shader program: " << "\n";
		return false;
	}

	// Attaching shader.
	glAttachShader(m_programID, vertShaderID);
	glAttachShader(m_programID, fragShaderID);

	int result = 0;
	glLinkProgram(m_programID);
	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

		std::cerr << "Error Linking shader Program: " << "\n";
		for (auto log : infoLog)
		{
			std::cout << log;
		}
		return false;
	}

	glValidateProgram(m_programID);
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE)
	{
		std::cerr << "Error Linking shader Program: " << "\n";
		return false;
	}

	m_uniformModel = glGetUniformLocation(m_programID, "model");
	m_uniformProjection = glGetUniformLocation(m_programID, "projection");

	// Deleting shaders.
	glDeleteShader(vertShaderID);
	glDeleteShader(fragShaderID);

	// Closing File.
	vertShaderFile.close();
	fragShaderFile.close();

	return true;
}

unsigned int Shader::CompileShaderSource(const char* shaderCode, GLenum shaderType)
{
	unsigned int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, nullptr);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

		std::cerr << "Compilation Error in shader: " << "\n";
		for(auto log : infoLog)
		{
			std::cout << log;
		}

		glDeleteShader(shaderID);
		return -1;
	}

	return shaderID;
}

GLuint Shader::GetProjectionLocation()
{
	return m_uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return m_uniformModel;
}

GLuint Shader::GetProgramID()
{
	return m_programID;
}

void Shader::UseShader()
{
	glUseProgram(m_programID);
}

void Shader::ClearShader()
{
	if (m_programID != 0)
	{
		glDeleteProgram(m_programID);
		m_programID = 0;
	}

	m_uniformProjection = 0;
	m_uniformModel = 0;
}

Shader::~Shader()
{
	ClearShader();
}