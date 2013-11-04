// Renderer.cpp

#include "Renderer.h"
#include "Mesh.h"
#include <forward_list>
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

	// Create an iterator
	std::forward_list<Mesh*>::iterator iter;

	//Iterate throught the render queue
    for (iter = rqueue.begin() ; iter != rqueue.end(); iter++){

		// Bind the mesh
		glBindVertexArray( (*iter)->vao );

		//Draw the mesh
		glDrawElements( GL_TRIANGLES, (*iter)->elements/4, GL_UNSIGNED_INT, 0 );
	};
	
	glBindVertexArray( 0 );

	//update the screen
	glfwSwapBuffers( window );

	return 0;
}