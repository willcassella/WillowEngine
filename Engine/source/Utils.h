#ifndef UTILS_H_
#define UTILS_H_

#include <GL\glew.h>
#include <vector>
#include "Vertex.h"

bool loadBinaryModel(
    const char * path,
    std::vector < Vertex > & out_vertices,
	std::vector < GLuint > & out_elements
);

#endif