#include "Camera.h"
#include "Renderer.h"

#include <glm\glm.hpp>

Camera::Camera()
{
	//Assign defaults
	fov = 45.0f;
	ratio = 1024.0f/768.0f;
	near = 1.0f;
	far = 40.0f;

	//Generate the projection matrix
	perspective = glm::perspective( fov, ratio, near, far );
	
	//Add the camera to the camera queue
	Renderer::cqueue.push( this );
}

Camera::~Camera()
{
	//Do nothing
}

void Camera::Update( GLFWwindow* window )
{
	transform.local.x = 1*sin( glfwGetTime()/2 );
}