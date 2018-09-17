#pragma once
#include "context.h"

#include <cstdio>
#include <iostream>
//MUST BE IN THIS ORDER OR THINGS WILL BREAK
#include "glew/glew.h"
#include "glfw/glfw3.h"
// Error callback called by OpenGL whenever a problem occurs (vendor-dependent)
void APIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message,
	const void *userParam)
{
	std::cerr << message << std::endl;
}

bool context::init(int width, int height, const char * title)
{
	//init glfw
	glfwInit();
	window = glfwCreateWindow(width, height, title, 
								nullptr, nullptr);
	glfwMakeContextCurrent(window);
	//init glew
	glewInit();

	//print out some diagnostics
	printf("DIAGNOSTICS\n================================================================================");
	printf("OpenGL Version %s\n", (const char *)glGetString(GL_VERSION));
	printf("Renderer: %s\n", (const char *)glGetString(GL_RENDERER));
	printf("Vendor: %s\n", (const char *)glGetString(GL_VENDOR));
	printf("GLSL: %s\n", (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

	printf("\n================================================================================DEBUG\n================================================================================\n");
	
	//debug 
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

	glClearColor(0.25f, 0.25f, 0.25, 1);
	
	return true;
}

void context::tick()
{
	//tracks things like key events 
	glfwPollEvents();
	//swaps buffers
	glfwSwapBuffers(window);
}

void context::term()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool context::shouldClose() const
{
	return glfwWindowShouldClose(window);
}


