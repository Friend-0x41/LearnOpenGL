#include "HelloTriangle.h"

HelloTriangle::HelloTriangle(unsigned int screenWidth,unsigned int screenHeight)
	:GLWindowBase{ "Hello Triangle",screenWidth,screenHeight },
	_vertices{-0.5f,-0.5f,0.0f,0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f}
{
	_vertexShaderSource = R"(#version 330 core
layout(location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0f);
})";

	_fragmentShaderSource = R"(#version 330 core
out vec4 FragColor;
void main()
{
	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);
})";

	init();
}

HelloTriangle::~HelloTriangle()
{
	if (_window)
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
		glDeleteProgram(_shaderProgram);
	}
}

bool HelloTriangle::init()
{
	if (!_window)
	{
		return false;
	}
	int vertexShader, fragmentShader;
	initShaders(vertexShader, fragmentShader);
	initShaderProgram(vertexShader, fragmentShader);
	initBuffers();
	return true;
}

void HelloTriangle::initShaders(int& vertexShader,int& fragmentShader)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* source = _vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Failed to compile vertex shader\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = _fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &source, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Failed to compile fragment shader\n" << infoLog << std::endl;
	}
}

void HelloTriangle::initShaderProgram(int vertexShader, int fragmentShader)
{
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);

	int success;
	char infoLog[512];

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
		std::cout << "Failed to link shader program\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void HelloTriangle::initBuffers()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void HelloTriangle::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int HelloTriangle::show()
{
	if (!_window)
	{
		return 1;
	}

	while (!glfwWindowShouldClose(_window))
	{
		process_input();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(_shaderProgram);
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}

	return 0;
}

void HelloTriangle::process_input()
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, true);
	}
}