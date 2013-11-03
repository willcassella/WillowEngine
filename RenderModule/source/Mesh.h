#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "Material.h"

class Mesh
{
public:
	
	Mesh( float _vertices[], int vertsize, int _elements[], int elemsize );
	~Mesh();

	GLuint vbo;
	GLuint ebo;
	void *vertices;
	void *elements;

	//TODO: allow multiple materials
	Material *mat;

	//Static meshes
	//static Mesh square;

	static float square_data[];

private:
	void static initMesh( Mesh *mesh );
};

#endif