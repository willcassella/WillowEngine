#include "Camera.h"
#include "Renderer.h"

#include <glm\glm.hpp>

Camera::Camera()
{
	//Assign defaults
	fov = 45.0f;
	ratio = 1024.0f/768.0f;
	near = 0.2f;
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
	double xpos, ypos;
	glfwGetCursorPos( window, &xpos, &ypos );

	transform.orientation.rotateByAxisAngle( Vec3( 0, 1, 0 ), -(xpos-512)/1000, false );
	transform.orientation.rotateByAxisAngle( Vec3( 1, 0, 0 ), (ypos-384)/1000, true );

	float speed = 0.02f;
	if( glfwGetKey( window, 340 ) )
		speed = 0.05f;
	
	glfwSetCursorPos( window, 512, 384 );

	if( glfwGetKey( window, 87 ) )
		transform.translateLocal( Vec3( 0, 0, speed ) );

	if( glfwGetKey( window, 83 ) )
		transform.translateLocal( Vec3( 0, 0, -speed ) );

	if( glfwGetKey( window, 65 ) )
		transform.translateLocal( Vec3( speed, 0, 0 ) );

	if( glfwGetKey( window, 68 ) )
		transform.translateLocal( Vec3( -speed, 0, 0 ) );
}