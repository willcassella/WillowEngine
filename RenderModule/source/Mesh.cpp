// Mesh.cpp

#include <GL\glew.h>
#include "Mesh.h"
#include "Renderer.h"

// Constructor
Mesh::Mesh( float _vertices[], int vertsize, GLuint _elements[], int elemsize )
{
	vertices = _vertices;
	elements = _elements;
	
	//Generate buffers and upload data
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, vertsize, _vertices, GL_STATIC_DRAW );

	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, elemsize, _elements, GL_STATIC_DRAW );

	// TODO: move this to scene class
	Renderer::rqueue.push_front( this );
}

Mesh::~Mesh()
{
	glDeleteBuffers( 1, &vbo );
}

float Mesh::square_data[] = {
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right

     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // Top-left
};

//Mesh Mesh::square ( Mesh::square_data );