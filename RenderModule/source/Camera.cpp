#include "Camera.h"
#include "Renderer.h"

#include "Mat4.h"

Camera::Camera()
{
	//Assign defaults
	vFOV = 43;
	ratio = 1280.0f/768.0f;
	zMin = 0.2f;
	zMax = 60.0f;

	//Generate the projection matrix
	perspective = Mat4::perspectiveVFOV( vFOV, ratio, zMin, zMax );
	
	//Add the camera to the camera queue
	Renderer::cqueue.push( this );
}

Camera::Camera( float _HFOV, float _RATIO, float _ZMIN, float _ZMAX )
{
	vFOV = _HFOV;
	ratio = _RATIO;
	zMin = _ZMIN;
	zMax = _ZMAX;

	perspective = Mat4::perspectiveVFOV( vFOV, ratio, zMin, zMax );

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


	transform.rotate( Vec3( 0, 1, 0 ), ((float)xpos-512)/500, false );
	transform.rotate( Vec3( 1, 0, 0 ), ((float)ypos-384)/500, true );

	float speed = 0.002f;
	if( glfwGetKey( window, 340 ) )
		speed = 0.005f;
	
	glfwSetCursorPos( window, 512, 384 );

	// Move forward
	if( glfwGetKey( window, 87 ) )
		transform.translate( Vec3( 0, 0, -speed ), true );

	// Move backward
	if( glfwGetKey( window, 83 ) )
		transform.translate( Vec3( 0, 0, speed ), true );

	// Move left
	if( glfwGetKey( window, 65 ) )
		transform.translate( Vec3( -speed, 0, 0 ), true );

	// Move right
	if( glfwGetKey( window, 68 ) )
		transform.translate( Vec3( speed, 0, 0 ), true );

	// Move up
	if( glfwGetKey( window, 81 ) )
		transform.translate( Vec3( 0, speed, 0 ), false );

	// Move down
	if( glfwGetKey( window, 69 ) )
		transform.translate( Vec3( 0, -speed, 0 ), false );
}