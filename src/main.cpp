
#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/glfw3.h"

#include <iostream>

#include "Window/Graphics.h"


using namespace std;

// Main Graphics Object.
Graphics graphics;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    graphics.Resize(width, height);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
    }
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
    }
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}


void joystick_callback(int joy, int event)
{
    if (event == GLFW_CONNECTED)
    {
    }
    else if (event == GLFW_DISCONNECTED)
    {
    }
}


int main(int argc, char* argv[])
{
    /* Initialize GLFW */
    if (!glfwInit())
        return -1;

    /* Create a window and its OpenGL context */
    bool fullscreen = false;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set callback functions */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetJoystickCallback(joystick_callback);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -2;
    }

    /* Show OpenGL context information */
    GLContextInfo infos = graphics.GetContextInfos();
    cout << "OpenGL version: " << infos.Version.Major << "." << infos.Version.Minor << endl;
    cout << "Driver version: " << infos.Version.Driver << endl;
    cout << "GLSL version: " << infos.Version.ShadingLanguage << endl;
    cout << "Vendor: " << infos.Vendor << endl;
    cout << "Renderer: " << infos.Renderer << endl;
    
    /* Initialize graphics subsystem */
    int width = 0, height = 0;
    
    glfwGetFramebufferSize(window, &width, &height);
    if (!graphics.Initialize(width, height,
        "..\\src\\Resources\\Shaders\\PassThruVert.vert",
        "..\\src\\Resources\\Shaders\\PassThruFrag.frag"))
    {
        glfwTerminate();
        return -3;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        graphics.Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    graphics.CleanUp();

    glfwTerminate();
    return 0;
}