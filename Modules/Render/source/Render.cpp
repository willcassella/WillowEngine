// Render.cpp

#include "glew.h"
#include "..\include\Render\Render.h"

void Render::InitRenderer(API::API API)
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Set the opengl clear color to black and clear the screen and the depth buffer
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::clearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}