#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include <GL\glew.h>

bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
	std::vector < GLuint    > & out_elements,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
);

#endif