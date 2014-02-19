#include "Camera.h"
#include "Scene.h"

#include "Mat4.h"

////////////////////////
///   Constructors   ///
////////////////////////

Camera::Camera( const float _VFOV, const float _RATIO, const float _ZMIN, const float _ZMAX )
{
	this->vFOV = _VFOV;
	this->ratio = _RATIO;
	this->zMin = _ZMIN;
	this->zMax = _ZMAX;

	this->perspective = Mat4::perspectiveVFOV( this->vFOV, this->ratio, this->zMin, this->zMax );
}

Camera::~Camera()
{
	//Do nothing
}

///////////////////////////////
///   Getters and Setters   ///
///////////////////////////////

Mat4 Camera::getPerspective()
{
	return this->perspective;
}

///////////////////
///   Methods   ///
///////////////////

void Camera::Update( GLFWwindow* const window )
{
	double xpos, ypos;
	glfwGetCursorPos( window, &xpos, &ypos );

	transform.rotate( Vec3( 0, 1, 0 ), ((float)xpos-512)/500, false );
	transform.rotate( Vec3( 1, 0, 0 ), ((float)ypos-384)/500, true );

	float speed = 0.04f;
	if( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) )
		speed = 0.09f;
	
	glfwSetCursorPos( window, 512, 384 );
	Vec3 movement = Vec3::ZERO;

	// Move forward
	if( glfwGetKey( window, GLFW_KEY_W ) )
		movement += Vec3::FORWARD;

	// Move backward
	if( glfwGetKey( window, GLFW_KEY_S ) )
		movement += Vec3::FORWARD * -1;

	// Move left
	if( glfwGetKey( window, GLFW_KEY_A ) )
		movement += Vec3::RIGHT * -1;

	// Move right
	if( glfwGetKey( window, GLFW_KEY_D ) )
		movement += Vec3::RIGHT;

	if( movement != Vec3::ZERO )
		transform.translate( movement.normalize()*speed, true );

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