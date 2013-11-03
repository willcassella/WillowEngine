#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "Material.h"

class Mesh
{
public:
	Mesh( const GLvoid *_vertices, Material *_mat );
	~Mesh();

	GLuint vbo;
	const GLvoid *vertices;

	//TODO: allow multiple materials
	Material *mat;

	//Static meshes
	static Mesh square;
};

#endif