// Renderer.cpp

#include "Renderer.h"
#include <SDL.h>

RenderQueue Renderer::rqueue;

int Renderer::init()
{
	// Set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	return 0;
}

int Renderer::render( SDL_Window* window )
{
	glClear( GL_COLOR_BUFFER_BIT );

	//select the front mesh
	Mesh *current_mesh = rqueue.front();

	//draw the mesh
	//glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	
	//update the screen
	SDL_GL_SwapWindow( window );

	return 0;
}