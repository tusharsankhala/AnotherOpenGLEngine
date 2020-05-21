#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"

#include <string>
#include <list>

struct Shader
{
	std::string LoadTextFile(const std::string& filepath);
	std::string ShaderTypeName(GLuint shader);
	bool CompileShader(GLuint shader, const std::string& sourcecode);
	std::string ShaderInfoLog(GLuint shader);
	bool LinkProgram(GLuint program, const std::list<GLuint>& shaderlist);
	std::string ProgramInfoLog(GLuint program);
};

#endif // SHADER_H