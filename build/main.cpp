// build.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../src/Renderer/GLRenderer.h"
#include "../src/Utils/MathUtils.h"

#include <iostream>

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    const std::string windowTitle = "OpenGL Window";

    // Initialize GLFW.
    if (!glfwInit())
    {
        std::cout << "GLFW Initialize Failed" << "\n";
        glfwTerminate();

        return -1;
    }

    // Setup GLFW window property.
    // OpenGL Version.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile (No Backward Compatibility).
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, windowTitle.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Window Creation failed" << "\n";
        glfwTerminate();
        return -1;
    }

    // Get buffer size information.
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Set current context for GLew to Use.
    glfwMakeContextCurrent(window);

    // Allow modern extnesion features.
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Glew InitWindow failed" << "\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Setup viewport size.
    glViewport(0, 0, bufferWidth, bufferHeight);

    GLRenderer renderer;
    renderer.InitializeRenderer();

    float rotationUpdate = 0.0f;
    float scaleUpdate = 0.0f;
    // Loop until window closed.
    while (!glfwWindowShouldClose(window))
    {
        // Get + Handle user input events.
        glfwPollEvents();

       if (renderer.directionIncrement > 1.0f)
            renderer.direction = false;

        if (renderer.directionIncrement < -1.0f)
            renderer.direction = true;
        
        if (renderer.direction)
        {
            renderer.directionIncrement += 0.01f;
        }
        else
        {
            renderer.directionIncrement -= 0.01f;
        }
       
        // Clear Window.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 modelMat(1.0f);
        //modelMat = glm::translate(modelMat, glm::vec3(renderer.directionIncrement, renderer.directionIncrement, 0.0f));
        modelMat = glm::rotate(modelMat, rotationUpdate * degToRadians, glm::vec3(0.0f, 0.0f, 1.0f));
        //modelMat = glm::scale(modelMat, scaleUpdate * glm::vec3(2.0f, 2.0f, 1.0f));

        glUseProgram(renderer.m_programID);
        //glUniform1f(renderer.uniformModel, renderer.directionIncrement);
        glUniformMatrix4fv(renderer.uniformModel, 1, false, glm::value_ptr(modelMat));
            glBindVertexArray(renderer.m_VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);

        rotationUpdate += 1.0f;
        scaleUpdate += 0.001f;
    }

    return 0;
}