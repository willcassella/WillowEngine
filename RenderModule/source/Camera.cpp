#include "Camera.h"
#include "Renderer.h"

Camera::Camera()
{
	//Assign defaults
	fov = 45.0f;
	ratio = 800.0f/600.0f;
	near = 1.0f;
	far = 10.0f;

	//Generate the projection matrix
	perspective = glm::perspective( fov, ratio, near, far );
	
	//Add the camera to the camera queue
	Renderer::cqueue.push( this );
}

Camera::~Camera()
{
	//Do nothing
}

void Camera::Update()
{
	//do nothing;
}