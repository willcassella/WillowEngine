#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <Engine.h>

class Renderer
{
public:

	static int init();

	static int render( const Scene& scene );
};

#endif