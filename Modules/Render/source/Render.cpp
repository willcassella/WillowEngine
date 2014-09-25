// Render.cpp

#include "glew.h"
#include "..\include\Render\Render.h"

void Willow::InitRenderer(API api)
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Set the OpenGL clear color to black and clear the screen and the depth buffer
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Willow::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}