#include "Graphics.h"

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "../Mesh/Mesh.h"
#include "../Shader/Shader.h"

using namespace glm;


uvec2 framebuffersize(0, 0);

GLuint program = 0;
GLuint vertexshader = 0;
GLuint fragmentshader = 0;
GLuint vertexarray = 0;
GLuint vertexbuffer = 0;


bool Graphics::Initialize(unsigned int width, unsigned int height,
                          const std::string& vertFilePath, const std::string& fragFilePath)
{
    /* set view port */
    Resize(width, height);

    /* general settings */
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f); /* background gray */

    /* create all objects */
    program = glCreateProgram();
    vertexshader = glCreateShader(GL_VERTEX_SHADER);
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glGenVertexArrays(1, &vertexarray);
    glGenBuffers(1, &vertexbuffer);

    Shader shader;

    // Shader Source.
    const std::string vertexshader_source = shader.LoadTextFile(vertFilePath);
    const std::string fragmentshader_source = shader.LoadTextFile(fragFilePath);

    /* compile shaders */
    if (!shader.CompileShader(vertexshader, vertexshader_source))
        return false;
    if (!shader.CompileShader(fragmentshader, fragmentshader_source))
        return false;

    /* link program */
    std::list<GLuint> shaderlist;
    shaderlist.push_back(vertexshader);
    shaderlist.push_back(fragmentshader);
    if (!shader.LinkProgram(program, shaderlist))
        return false;

    /* setup vertexarray */
    glBindVertexArray(vertexarray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(float) * 0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    /* setup vertexbuffer */
    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(vec3(0, 0, 0)));
    vertices.push_back(Vertex(vec3(1, 0, 0)));
    vertices.push_back(Vertex(vec3(0, 1, 0)));
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* successfully initialized */
    return true;
}


void Graphics::CleanUp()
{
    /* destroy all objects */
    glDeleteProgram(program);
    glDeleteShader(vertexshader);
    glDeleteShader(fragmentshader);
    glDeleteVertexArrays(1, &vertexarray);
    glDeleteBuffers(1, &vertexbuffer);
}


void Graphics::Render()
{
    /* clear framebuffer */
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw triangle */
    glUseProgram(program);
    glBindVertexArray(vertexarray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}


void Graphics::Resize(unsigned int width, unsigned int height)
{
    framebuffersize = uvec2(width, height);
    glViewport(0, 0, width, height);
}


GLContextInfo Graphics::GetContextInfos()
{
    GLContextInfo infos;

    glGetIntegerv(GL_MAJOR_VERSION, &infos.Version.Major);
    glGetIntegerv(GL_MINOR_VERSION, &infos.Version.Minor);
    infos.Version.Driver = (const char*)glGetString(GL_VERSION);
    infos.Vendor = (const char*)glGetString(GL_VENDOR);
    infos.Renderer = (const char*)glGetString(GL_RENDERER);
    infos.Version.ShadingLanguage = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint numberofextensions = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numberofextensions);
    for (int i = 0; i < numberofextensions; i++)
        infos.SupportedExtensions.push_back((const char*)glGetStringi(GL_EXTENSIONS, i));

    GLint numberofsupportedglslversions = 0;
    glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &numberofsupportedglslversions);
    for (int i = 0; i < numberofsupportedglslversions; i++)
        infos.SupportedGLSLVersions.push_back((const char*)glGetStringi(GL_SHADING_LANGUAGE_VERSION, i));

    return infos;
}