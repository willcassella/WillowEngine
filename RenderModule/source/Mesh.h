#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include <GL/glew.h>
#include "Material.h"

typedef std::vector<glm::vec3>	VertexArray;
typedef std::vector<GLuint>		ElementArray;

class Mesh
{
public:
	
	Mesh();
	Mesh( const char * path );
	~Mesh();

	// Load buffers to video card
	void Load( const char * path );

	// Assign a material
	void AssignMat( Material *_mat );

	// Delete buffers from video card
	void Unload();

	// Buffer information
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	
	VertexArray vertices;
	ElementArray elements;
	std::vector < glm::vec2 > uv;
    std::vector < glm::vec3 > normal;

private:

	// Holds whether the mesh has been loaded to the video card
	bool loaded;

	//TODO: allow multiple materials
	Material *mat;

	//Material information
	GLuint posAttrib;
	GLuint colAttrib;
};

#endif