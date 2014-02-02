#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>
#include <GL/glew.h>
#include "Material.h"
#include "Vertex.h"

typedef std::vector< Vertex> VertexArray;
typedef std::vector< GLuint> ElementArray;

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

	//TODO: allow multiple materials
	Material *mat;

private:

	// Holds whether the mesh has been loaded to the video card
	bool loaded;
};

#endif