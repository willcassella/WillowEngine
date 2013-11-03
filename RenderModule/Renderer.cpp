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

	// Render the only mesh in the queue
	Mesh *current_mesh = rqueue.front();

	// Bind the mesh's material
	glUseProgram( current_mesh->mat->id );

	glDrawArrays( GL_TRIANGLES, 0, 6 );
	
	SDL_GL_SwapWindow( window );

	return 0;
}