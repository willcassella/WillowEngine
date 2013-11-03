// Renderer.cpp

#include "Renderer.h"
#include <SDL.h>

RenderQueue Renderer::rqueue;

int Renderer::init()
{
	// set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	return 0;
}

int Renderer::render( SDL_Window* window )
{
	glClear( GL_COLOR_BUFFER_BIT );

	// Render the only mesh in the queue
	Mesh *current_mesh = rqueue.front();

	// Bind the meshe's material
	glUseProgram( current_mesh->mat->id );
	
	SDL_GL_SwapWindow( window );
}