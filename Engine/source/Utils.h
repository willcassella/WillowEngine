#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>
#include <GL\glew.h>
#include "Vertex.h"

bool loadBinaryModel(
    const std::string& path,
    std::vector < Vertex >* out_vertices,
	std::vector < GLuint >* out_elements
);

#endif