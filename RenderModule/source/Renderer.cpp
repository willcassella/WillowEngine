// Renderer.cpp

#include "Renderer.h"
#include <GLFW\glfw3.h>

RenderQueue Renderer::rqueue;

int Renderer::init()
{
	// Set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	return 0;
}

int Renderer::render( GLFWwindow* window )
{
	glClear( GL_COLOR_BUFFER_BIT );

	//select the front mesh
	Mesh *current_mesh = rqueue.front();

	//draw the mesh
	//glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	
	//update the screen
	glfwSwapBuffers( window );

	return 0;
}