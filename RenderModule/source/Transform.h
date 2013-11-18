#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#include "Quaternion.h"

struct Transform
{
	glm::vec3 local;
	Quaternion orientation;
	glm::vec3 scale;
	
	glm::vec3 getGlobal()
	{
		//TODO: add parenting support
		return local;
	}
};

#endif