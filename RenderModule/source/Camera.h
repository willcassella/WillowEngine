#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Transform.h"
#include "Mat4.h"

class Camera
{
public:
	
	Camera();
	~Camera();
	
	Transform transform;
	void Update( GLFWwindow* window );

	float hFOV;
	float ratio;
	float near;
	float far;

	Mat4 perspective;
};

#endif