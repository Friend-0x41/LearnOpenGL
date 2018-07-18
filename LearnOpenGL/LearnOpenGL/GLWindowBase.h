#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>

class GLWindowBase
{
public:

	~GLWindowBase();

	virtual int show();

	GLWindowBase(const GLWindowBase& w) = delete;

	GLWindowBase(const GLWindowBase&& w) = delete;

	GLWindowBase& operator=(const GLWindowBase& w) = delete;

protected:

	GLWindowBase(std::string windowName, unsigned int width, unsigned int height);

	virtual bool init();

	virtual bool initContext();

	virtual void process_input() = 0;

	virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:

	friend void mframebuffer_size_process(GLFWwindow* window, int width, int height);

protected:

	GLFWwindow * _window = nullptr;

	const unsigned int ScreenWidth;

	const unsigned int ScreenHeight;

	std::string _windowName;
};