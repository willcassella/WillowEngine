#include "Camera.h"
#include "Renderer.h"

#include <glm\glm.hpp>
//experimental
#include <math.h>

Camera::Camera()
{
	//Assign defaults
	fov = 45.0f;
	ratio = 1920.0f/1080.0f;
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
	//double x, y;
	//glfwGetCursorPos( window, &x, &y );

	//transform.euler.x = (GLfloat)x/700;
	//transform.euler.y = (GLfloat)y/400;
	transform.local.x = 3*sin( glfwGetTime()/2 );
	transform.local.y = 3*cos( glfwGetTime()/2 );
}