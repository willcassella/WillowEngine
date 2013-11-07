#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm\gtc\matrix_transform.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 coordinates;
	glm::vec3 normal;
};

#endif