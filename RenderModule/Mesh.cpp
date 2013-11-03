// Mesh.cpp

#include <GL\glew.h>
#include "Mesh.h"
#include "Renderer.h"

// Constructor
Mesh::Mesh( const GLvoid *_vertices, Material *_mat )
{
	vertices = _vertices;
	mat = _mat;
	
	//Generate buffers and upload data
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_DYNAMIC_DRAW );

	// TODO: move this to scene class
	Renderer::rqueue.push( this );
}

Mesh::~Mesh()
{
	glDeleteBuffers( 1, &vbo );
}

float square_vertices[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right

     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // Top-left
};

Mesh Mesh::square ( square_vertices, &Material::basic );