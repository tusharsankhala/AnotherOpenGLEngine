// build.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../src/Utils/MathUtils.h"
#include "Window/Window.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const std::string windowTitle = "OpenGL Window";

    std::vector<Mesh*> meshList;

    GLRendererWindow window = GLRendererWindow(WIDTH, HEIGHT, windowTitle.c_str());
    int status = window.Initialize();
    if (status == -1)
    {
        std::cerr << "Window Creation failed" << "\n";
        return -1;
    }
        
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] =
    {
        -1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
    };

    Mesh* mesh1 = new Mesh();
    mesh1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(mesh1);

    float rotationUpdate = 0.0f;
  
    // Projection Matrix.
    glm::mat4 projectionMat = glm::perspective(45.0f, window.GetBufferWidth() / window.GetBufferHeight(), 0.1f, 100.0f);

    Shader* shader = new Shader();
    bool shaderStatus = shader->LoadShaderFromFile("E:\\GitReposMy\\AnotherOpenGLEngine\\src\\Shaders\\PassThruVert.vert",
        "E:\\GitReposMy\\AnotherOpenGLEngine\\src\\Shaders\\PassThruFrag.frag");

    GLuint programID = shader->GetProgramID();
    GLuint uniformModel = 0;
    GLuint uniformProjection = 0;

    if (!shaderStatus)
    {
        std::cerr << "Shader compilation failed, Aborting program" << "\n";
        return -1;
    }

    // Loop until window closed.
    while (!window.GetShouldClose())
    {
        // Get + Handle user input events.
        glfwPollEvents();

        // Clear Window.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->UseShader();
        uniformModel = shader->GetModelLocation();
        uniformProjection = shader->GetProjectionLocation();
       
        glm::mat4 modelMat(1.0f);

        modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -5.5f));
        modelMat = glm::rotate(modelMat, rotationUpdate * degToRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        modelMat = glm::scale(modelMat, glm::vec3(0.7f, 0.7f, 0.7f));

        meshList[0]->RenderMesh();

        glUseProgram(programID);
        glUniformMatrix4fv(uniformModel, 1, false, glm::value_ptr(modelMat));
        glUniformMatrix4fv(uniformProjection, 1, false, glm::value_ptr(projectionMat));
        
        glUseProgram(0);

        window.SwapBuffers();

        rotationUpdate += 1.0f;
    }

    return 0;
}