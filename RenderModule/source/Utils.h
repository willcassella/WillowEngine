#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include "Vertex.h"
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>

bool loadOBJ(
    const char * path,
    std::vector < Vertex > & out_vertices,
	std::vector < GLuint > & out_elements
);

#endif