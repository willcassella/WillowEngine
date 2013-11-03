// Mesh.cpp

#include <GL\glew.h>
#include "Mesh.h"
#include "Renderer.h"

// Constructor
Mesh::Mesh( float _vertices[], int size )
{
	vertices = _vertices;
	
	//Generate buffers and upload data
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	glBufferData( GL_ARRAY_BUFFER, size, _vertices, GL_STATIC_DRAW );

	// TODO: move this to scene class
	Renderer::rqueue.push( this );
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