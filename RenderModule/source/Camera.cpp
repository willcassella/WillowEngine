#include "Camera.h"
#include "Renderer.h"

#include "Mat4.h"

Camera::Camera()
{
	//Assign defaults
	hFOV = 60;
	ratio = 1280.0f/768.0f;
	near = 0.2f;
	far = 40.0f;

	//Generate the projection matrix
	perspective = Mat4::perspectiveFOV( hFOV, ratio, near, far );
	
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

	transform.rotate( Vec3( 0, 1, 0 ), -(xpos-512)/500, false );
	transform.rotate( Vec3( 1, 0, 0 ), (ypos-384)/500, true );

	float speed = 0.002f;
	if( glfwGetKey( window, 340 ) )
		speed = 0.005f;
	
	glfwSetCursorPos( window, 512, 384 );

	if( glfwGetKey( window, 87 ) )
		transform.translate( Vec3( 0, 0, speed ), true );

	if( glfwGetKey( window, 83 ) )
		transform.translate( Vec3( 0, 0, -speed ), true );

	if( glfwGetKey( window, 65 ) )
		transform.translate( Vec3( speed, 0, 0 ), true );

	if( glfwGetKey( window, 68 ) )
		transform.translate( Vec3( -speed, 0, 0 ), true );
}