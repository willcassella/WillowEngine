// Mesh.cpp

#include <GL\glew.h>
#include "Mesh.h"
#include "Renderer.h"

// Constructors
Mesh::Mesh()
{
	loaded = false;
}

Mesh::Mesh( float _vertices[], int vertsize, GLuint _elements[], int elemsize )
{
	elements = elemsize;

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	//Generate buffers and upload data
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, vertsize, _vertices, GL_STATIC_DRAW );

	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, elemsize, _elements, GL_STATIC_DRAW );

	glBindVertexArray( 0 );

	// TODO: move this to scene class
	Renderer::rqueue.push_front( this );

	loaded = true;
}

Mesh::~Mesh()
{
	Unload();
}

void Mesh::Load( float _vertices[], int vertsize, GLuint _elements[], int elemsize )
{
	elements = elemsize;

	if( !loaded )
		glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	//Generate buffers and upload data
	if( !loaded )
		glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, vertsize, _vertices, GL_STATIC_DRAW );

	if( !loaded )
		glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, elemsize, _elements, GL_STATIC_DRAW );

	// TODO: move this to scene class
	Renderer::rqueue.push_front( this );

	glBindVertexArray( 0 );

	loaded = true;
}

void Mesh::Unload()
{
	if( loaded )
	{
		glDeleteBuffers( 1, &vbo );
		glDeleteBuffers( 1, &ebo );
		glDeleteVertexArrays( 1, &vao );
	}
	loaded = false;
}

void Mesh::AssignMat( Material *_mat )
{
	mat = _mat;

	glBindVertexArray( vao );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );

	posAttrib = glGetAttribLocation( mat->id, "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0 );

    colAttrib = glGetAttribLocation( mat->id, "color" );
    glEnableVertexAttribArray( colAttrib );
    glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)) );

	glBindVertexArray( 0 );
}