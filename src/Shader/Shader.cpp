#include "Shader.h"

#include <iostream>
#include <fstream>


std::string Shader::LoadTextFile(const std::string& filepath)
{
    std::string result(""), line;
    std::fstream f(filepath.c_str(), std::ios::in);
    while (f.good())
    {
        std::getline(f, line);
        result += line + '\n';
    }
    return result;
}


std::string Shader::ShaderTypeName(GLuint shader)
{
    if (glIsShader(shader))
    {
        GLint type = 0;
        glGetShaderiv(shader, GL_SHADER_TYPE, &type);

        if (type == GL_VERTEX_SHADER)
            return "Vertex Shader";
        if (type == GL_TESS_CONTROL_SHADER)
            return "Tessellation Control Shader";
        if (type == GL_TESS_EVALUATION_SHADER)
            return "Tessellation Evaluation Shader";
        if (type == GL_GEOMETRY_SHADER)
            return "Geometry Shader";
        if (type == GL_FRAGMENT_SHADER)
            return "Fragment Shader";
        if (type == GL_COMPUTE_SHADER)
            return "Compute Shader";
    }

    return "invalid shader";
}


bool Shader::CompileShader(GLuint shader, const std::string& sourcecode)
{
    if (!glIsShader(shader))
    {
        std::cout << "ERROR: shader compilation failed, no valid shader specified" << std::endl;
        return false;
    }

    if (sourcecode.empty())
    {
        std::cout << "ERROR: shader compilation failed, no source code specified  (" << ShaderTypeName(shader) << ")" << std::endl;
        return false;
    }

    const char* sourcearray[] = { sourcecode.c_str() };
    glShaderSource(shader, 1, sourcearray, NULL);
    glCompileShader(shader);

    // check compile status
    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    // successfully compiled shader
    if (status == GL_TRUE)
        return true;

    // show compile errors
    std::cout << "ERROR: shader compilation failed  (" << ShaderTypeName(shader) << ")" << std::endl << ShaderInfoLog(shader) << std::endl;

    return false;
}


std::string Shader::ShaderInfoLog(GLuint shader)
{
    if (glIsShader(shader))
    {
        GLint logsize = 0;
        GLchar infolog[1024] = { 0 };
        glGetShaderInfoLog(shader, 1024, &logsize, infolog);

        return std::string(infolog);
    }

    return "invalid shader";
}


bool Shader::LinkProgram(GLuint program, const std::list<GLuint>& shaderlist)
{
    if (!glIsProgram(program))
    {
        std::cout << "ERROR: shader linking failed, no valid program specified" << std::endl;
        return false;
    }

    // attach all shaders to the program
    for (std::list<GLuint>::const_iterator it = shaderlist.begin(); it != shaderlist.end(); it++)
    {
        if (glIsShader(*it))
            glAttachShader(program, *it);
    }

    // link program
    glLinkProgram(program);

    // detach all shaders again
    for (std::list<GLuint>::const_iterator it = shaderlist.begin(); it != shaderlist.end(); it++)
    {
        if (glIsShader(*it))
            glDetachShader(program, *it);
    }

    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    // successfully linked program
    if (status == GL_TRUE)
        return true;

    // show link errors
    std::cout << "ERROR: shader linking failed" << std::endl << ProgramInfoLog(program) << std::endl;

    return false;
}


std::string Shader::ProgramInfoLog(GLuint program)
{
    if (glIsProgram(program))
    {
        GLint logsize = 0;
        GLchar infolog[1024] = { 0 };
        glGetProgramInfoLog(program, 1024, &logsize, infolog);

        return std::string(infolog);
    }

    return "invalid program";
}