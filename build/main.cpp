// build.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../src/Renderer/GLRenderer.h"

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


    // Loop until window closed.
    while (!glfwWindowShouldClose(window))
    {
        // Get + Handle user input events.
        glfwPollEvents();

        // Clear Window.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(renderer.m_programID);
            glBindVertexArray(renderer.m_VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);
            glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);
    }

    return 0;
}