#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <queue>
#include "GameObject.h"
#include "Camera.h"

#include "Mesh.h"
//TODO: change this to a queue
typedef std::queue<GameObject*>	RenderQueue;
typedef std::queue<Camera*>		CameraQueue;

class Renderer
{
public:

	static RenderQueue rqueue;
	static CameraQueue cqueue;

	static int init();

	static int render( GLFWwindow* window );
};

#endif