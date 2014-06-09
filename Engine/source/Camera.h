#ifndef CAMERA_H_
#define CAMERA_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "GameObject.h"
#include "Mat4.h"

class Camera : public GameObject
{
	REGISTER(Camera);

	////////////////////////
	///   Constructors   ///

	Camera(const float vFOV = 43, const float ratio = 1280.0f / 720, const float zMin = 0.1f, const float zMax = 90);
	~Camera();
	
	//////////////////
	///   Fields   ///
private:

	float vFOV;
	float ratio;
	float zMin;
	float zMax;
	Mat4 perspective;

	///////////////////
	///   Methods   ///
public:

	void Update( GLFWwindow* const window );
	Mat4 getPerspective();
};

#endif