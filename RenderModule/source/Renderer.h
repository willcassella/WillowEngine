#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL\glew.h>
#include <SDL.h>
#include <forward_list>

#include "Mesh.h"
//TODO: change this to a queue
typedef std::forward_list<Mesh*> RenderQueue;

class Renderer
{
public:
	static RenderQueue rqueue;

	static int init();

	static int render( SDL_Window* window );
};

#endif