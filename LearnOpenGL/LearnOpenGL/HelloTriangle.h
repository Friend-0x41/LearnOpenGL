#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include "GLWindowBase.h"

class HelloTriangle : public GLWindowBase
{
public:

	HelloTriangle(unsigned int screenWidth = 800, unsigned int screenHeight = 600);

	~HelloTriangle();

	virtual int show() override;

	virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height) override;

private:

	virtual bool init() override;

	void initShaders(int& vertexShader,int& fragmentShader);

	void initShaderProgram(int vertexShader, int fragmentShader);

	void initBuffers();

	void process_input() override;

private:

	unsigned int _vao = 0, _vbo = 0;

	int _shaderProgram = 0;

	std::string _vertexShaderSource;
	std::string _fragmentShaderSource;

	float _vertices[9];
};