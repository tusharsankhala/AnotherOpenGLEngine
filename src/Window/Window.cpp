#include "Window.h"

#include <iostream>

int GLRendererWindow::Initialize()
{
	if (!glfwInit())
	{
		std::cerr << "Error initializing GLFW"<<"\n";
		glfwTerminate();
		return -1;
	}

	// Setup GLFW Window Properties.
	// OpenGL version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Core Profile.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Allow Forward Compatibility.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window.
	m_mainWindow = glfwCreateWindow(m_winWidth, m_winHeight, m_winTitle.c_str(), NULL, NULL);
	if (!m_mainWindow)
	{
		std::cerr << "Failed to Create window" << "\n";
		glfwTerminate();
		return -1;
	}

	// Get buffer size information.
	glfwGetFramebufferSize(m_mainWindow, &m_winBufferWidth, &m_winBufferHeight);

	// Set the current context.
	glfwMakeContextCurrent(m_mainWindow);

	// Key and mOuse Callbacks.
	InitializeCallbacks();

	//Allow experimantal extension access.
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "Error:" << glewGetErrorString(error) << "\n";
		glfwDestroyWindow(m_mainWindow);
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// Create Viewport.
	glViewport(0, 0, m_winBufferWidth, m_winBufferHeight);

	glfwSetWindowUserPointer(m_mainWindow, this);

	return 0;
}

void GLRendererWindow::InitializeCallbacks()
{
	glfwSetKeyCallback(m_mainWindow, HandleKeys);
}

void GLRendererWindow::HandleKeys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode)
{
	GLRendererWindow* glRendererWindow = static_cast<GLRendererWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			glRendererWindow->m_keys[key] = true;
			std::cout << "Pressed" << key << "\n";
		}
		else if (action == GLFW_RELEASE)
		{
			glRendererWindow->m_keys[key] = false;
			std::cout << "Released" << key << "\n";
		}
	}
}

GLRendererWindow::~GLRendererWindow()
{
	glfwDestroyWindow(m_mainWindow);
	glfwTerminate();
}