// Camera.cpp

#include "..\include\Core\Camera.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Camera::Camera(const String& _name, float _vFOV, float _ratio, float _zMin, float _zMax)
	: Base(_name)
{
	this->vFOV = _vFOV;
	this->ratio = _ratio;
	this->zMin = _zMin;
	this->zMax = _zMax;

	this->perspective = Math::Mat4::perspectiveVFOV(vFOV, ratio, zMin, zMax);
}

///////////////////
///   Methods   ///

void Camera::tick(float timeInterval)
{
//	double xpos, ypos;
//	glfwGetCursorPos( window, &xpos, &ypos );
//
//	transform.rotate( Math::Vec3( 0, 1, 0 ), ((float)xpos-512)/500, false );
//	transform.rotate( Math::Vec3( 1, 0, 0 ), ((float)ypos-384)/500, true );
//
//	float speed = 0.04f;
//	if( glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) )
//		speed = 0.09f;
//	
//	glfwSetCursorPos( window, 512, 384 );
//	Math::Vec3 movement = Math::Vec3::ZERO;
//
//	// Move forward
//	if( glfwGetKey( window, GLFW_KEY_W ) )
//		movement += Math::Vec3::FORWARD;
//
//	// Move backward
//	if( glfwGetKey( window, GLFW_KEY_S ) )
//		movement += Math::Vec3::FORWARD * -1;
//
//	// Move left
//	if( glfwGetKey( window, GLFW_KEY_A ) )
//		movement += Math::Vec3::RIGHT * -1;
//
//	// Move right
//	if( glfwGetKey( window, GLFW_KEY_D ) )
//		movement += Math::Vec3::RIGHT;
//
//	if( movement != Math::Vec3::ZERO )
//		transform.translate( movement.normalize()*speed, true );
//
//	// Move up
//	if( glfwGetKey( window, GLFW_KEY_Q ) )
//		transform.translate( Math::Vec3( 0, speed, 0 ), false );
//
//	// Move down
//	if( glfwGetKey( window, GLFW_KEY_E ) )
//		transform.translate( Math::Vec3( 0, -speed, 0 ), false );
//
//	// Tilt left
//	if( glfwGetKey( window, GLFW_KEY_Z ) )
//		transform.rotate( Math::Vec3( 0, 0, 1 ), -0.008f , true );
//
//	// Tilt right
//	if( glfwGetKey( window, GLFW_KEY_X ) )
//		transform.rotate( Math::Vec3( 0, 0, 1 ), 0.008f , true );
}

Math::Mat4 Camera::getPerspective() const
{
	return perspective;
}