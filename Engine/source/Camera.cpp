#include "Camera.h"
#include "Scene.h"

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
}

Camera::Camera( float _HFOV, float _RATIO, float _ZMIN, float _ZMAX )
{
	vFOV = _HFOV;
	ratio = _RATIO;
	zMin = _ZMIN;
	zMax = _ZMAX;

	perspective = Mat4::perspectiveVFOV( vFOV, ratio, zMin, zMax );
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

	float speed = 0.04f;
	if( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) )
		speed = 0.09f;
	
	glfwSetCursorPos( window, 512, 384 );

	// Move forward
	if( glfwGetKey( window, GLFW_KEY_W ) )
		transform.translate( Vec3( 0, 0, -speed ), true );

	// Move backward
	if( glfwGetKey( window, GLFW_KEY_S ) )
		transform.translate( Vec3( 0, 0, speed ), true );

	// Move left
	if( glfwGetKey( window, GLFW_KEY_A ) )
		transform.translate( Vec3( -speed, 0, 0 ), true );

	// Move right
	if( glfwGetKey( window, GLFW_KEY_D ) )
		transform.translate( Vec3( speed, 0, 0 ), true );

	// Move up
	if( glfwGetKey( window, GLFW_KEY_Q ) )
		transform.translate( Vec3( 0, speed, 0 ), false );

	// Move down
	if( glfwGetKey( window, GLFW_KEY_E ) )
		transform.translate( Vec3( 0, -speed, 0 ), false );

	// Tilt left
	if( glfwGetKey( window, GLFW_KEY_Z ) )
		transform.rotate( Vec3( 0, 0, 1 ), -0.008f , true );

	// Tilt right
	if( glfwGetKey( window, GLFW_KEY_X ) )
		transform.rotate( Vec3( 0, 0, 1 ), 0.008f , true );
}