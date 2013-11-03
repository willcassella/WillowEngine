#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "Material.h"

class Mesh
{
public:
	
	Mesh( float _vertices[], int size );
	~Mesh();

	GLuint vao;
	GLuint vbo;
	void *vertices;

	//TODO: allow multiple materials
	Material *mat;

	//Static meshes
	//static Mesh square;

	static float square_data[];

private:
	void static initMesh( Mesh *mesh );
};

#endif