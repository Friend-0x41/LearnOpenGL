#include "GLWindowBase.h"

static GLWindowBase* instance = nullptr;

static void mframebuffer_size_process(GLFWwindow* window, int width, int height);

GLWindowBase::GLWindowBase(std::string windowName, unsigned int width, unsigned int height)
	:_windowName{ windowName }, ScreenWidth{ width }, ScreenHeight{ height }
{
	if (init())
	{
		instance = this;
	}
}

bool GLWindowBase::init()
{
	if (!initContext())
	{
		return false;
	}

	return true;
}

bool GLWindowBase::initContext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(ScreenWidth, ScreenHeight, _windowName.c_str(), nullptr, nullptr);
	if (!_window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, mframebuffer_size_process);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		_window = nullptr;
		return false;
	}
	return true;
}

GLWindowBase::~GLWindowBase()
{
	if (_window)
	{
		glfwTerminate();
	}
}

int GLWindowBase::show()
{
	if (!_window)
	{
		return -1;
	}

	while (!glfwWindowShouldClose(_window))
	{
		process_input();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
	return 0;
}

void GLWindowBase::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mframebuffer_size_process(GLFWwindow* window, int width, int height)
{
	if (instance)
	{
		instance->framebuffer_size_callback(window, width, height);
	}
}