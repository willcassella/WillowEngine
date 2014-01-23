#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

//#include "Quaternion.h"

struct Transform
{
	// Data
	glm::vec3 local;
	glm::quat orientation;
	glm::vec3 scale;
	
	// Returns the global position
	glm::vec3 getGlobal()
	{
		//TODO: add parenting support
		return local;
	}

	// Returns the model matrix
	glm::mat4 getModel()
	{
		return glm::translate( glm::mat4(), local ) * glm::mat4_cast( orientation );
	}
};

#endif