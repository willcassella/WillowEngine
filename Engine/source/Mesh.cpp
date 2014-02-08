// Mesh.cpp

#include <GL\glew.h>

#include "Mesh.h"
#include "Utils.h"
#include "Vertex.h"
#include "Vec3.h"

// Constructors
Mesh::Mesh()
{
	loaded = false;
}

Mesh::Mesh( const char * path )
{
	loadBinaryModel( path, vertices, elements );

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	//Generate buffers and upload data
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof( GLuint ), &elements[0] , GL_STATIC_DRAW );

	glBindVertexArray( 0 );

	loaded = true;
}

Mesh::~Mesh()
{
	Unload();
}

void Mesh::Load( const char * path )
{
	loadBinaryModel( path, vertices, elements );

	if( !loaded )
		glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	//Generate buffers and upload data
	if( !loaded )
		glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof( Vertex ), &vertices[0], GL_STATIC_DRAW);

	if( !loaded )
		glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof( GLuint ), &elements[0] , GL_STATIC_DRAW );

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
	
	GLuint posAttrib;
	posAttrib = glGetAttribLocation( mat->id, "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	GLint texAttrib = glGetAttribLocation( mat->id, "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)sizeof( Vec3 ) );

	GLuint colAttrib;
    colAttrib = glGetAttribLocation( mat->id, "color" );
    glEnableVertexAttribArray( colAttrib );
    glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)) );

	glBindVertexArray( 0 );
}