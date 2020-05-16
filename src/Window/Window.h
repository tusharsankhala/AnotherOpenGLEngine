#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GL/glfw3.h>

class GLRendererWindow
{
public:
	GLRendererWindow() : m_winWidth(800), m_winHeight(600), m_winTitle("OpenGL Window") {}

	GLRendererWindow(GLint width, GLint height, std::string title): m_winWidth(width), m_winHeight(height),
														  m_winTitle(title), m_mainWindow(nullptr)
	{}

	GLRendererWindow(const GLRendererWindow& win);
	GLRendererWindow& operator=(const GLRendererWindow& win) = delete;

	~GLRendererWindow();

	int Initialize();

	GLfloat GetBufferWidth() { return static_cast<GLfloat>(m_winWidth); }
	GLfloat GetBufferHeight() { return static_cast<GLfloat>(m_winHeight); }

	bool GetShouldClose() { return glfwWindowShouldClose(m_mainWindow); }
	
	void SwapBuffers() { glfwSwapBuffers(m_mainWindow); }

	bool GetKey(int key) { return m_keys[key]; }
	void SetKey(int key, bool val) { m_keys[key] = val; }

private:
	GLFWwindow* m_mainWindow;

	GLuint m_winWidth, m_winHeight;
	int m_winBufferWidth, m_winBufferHeight;

	std::string m_winTitle;

	bool m_keys[1024] = {false};

	// Callbacks.
	void InitializeCallbacks();


	// Handle Input Events.
	static void HandleKeys(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode);

};

#endif