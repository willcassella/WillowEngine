#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL\glew.h>
#include <SDL.h>
#include <queue>

#include "Mesh.h"
typedef std::queue<Mesh*> RenderQueue;

class Renderer
{
public:
	static RenderQueue rqueue;

	static int init();

	static int render( SDL_Window* window );
};

#endif