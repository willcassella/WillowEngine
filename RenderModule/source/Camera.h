#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Transform.h"
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	
	Camera();
	~Camera();
	
	Transform transform;
	void Update( GLFWwindow* window );

	float fov;
	float ratio;
	float near;
	float far;

	glm::mat4 perspective;
};

#endif