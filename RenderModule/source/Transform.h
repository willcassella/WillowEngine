#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm\gtc\matrix_transform.hpp>

typedef glm::vec3 Position;

struct Transform
{
	Position global;
	glm::vec3 scale;
	glm::vec3 rotation;
};

#endif