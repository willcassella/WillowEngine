#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <forward_list>

#include "Mesh.h"
//TODO: change this to a queue
typedef std::forward_list<Mesh*> RenderQueue;

class Renderer
{
public:

	static RenderQueue rqueue;

	static int init();

	static int render( GLFWwindow* window );
};

#endif