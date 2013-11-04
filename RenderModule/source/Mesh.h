#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <GL/glew.h>
#include "Material.h"

class Mesh
{
public:
	
	Mesh();
	Mesh( float _vertices[], int vertsize, GLuint _elements[], int elemsize );
	~Mesh();

	// Load buffers to video card
	void Load( float _vertices[], int vertsize, GLuint _elements[], int elemsize );

	// Assign a material
	void AssignMat( Material *_mat );

	// Delete buffers from video card
	void Unload();

	// Buffer information
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	GLuint elements;

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