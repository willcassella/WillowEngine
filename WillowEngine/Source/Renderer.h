#ifndef RENDERER_H_
#define RENDERER_H_

#include "RenderProgram.h"

class Renderer
{
private:
	GLuint vao;
	GLuint vbo;
public:
	Renderer();
	~Renderer();

	void Init();

	void compile();

	int render( SDL_Window* window );

	RenderProgram program;
};

#endif