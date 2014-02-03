#include "Camera.h"
#include "Renderer.h"

#include "Mat4.h"

Camera::Camera()
{
	//Assign defaults
	vFOV = 59;
	ratio = 1280.0f/768.0f;
	zMin = 0.2f;
	zMax = 40.0f;

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

	transform.rotate( Vec3( 0, 1, 0 ), -((float)xpos-512)/500, false );
	transform.rotate( Vec3( 1, 0, 0 ), ((float)ypos-384)/500, true );

	float speed = 0.02f;
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