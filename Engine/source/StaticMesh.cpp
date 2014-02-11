// StaticMesh.cpp

#include <string>
#include <GL\glew.h>
#include "StaticMesh.h"
#include "Utils.h"
#include "Vertex.h"
#include "Vec3.h"

////////////////////////
///   Constructors   ///
////////////////////////

StaticMesh::StaticMesh( const std::string& path )
{
	loadBinaryModel( path, &this->vertices, &this->elements );

	// Generate buffers and upload data
	glGenVertexArrays( 1, &this->vao );
	glBindVertexArray( this->vao );
	
	glGenBuffers( 1, &this->vbo );
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo );
	glBufferData( GL_ARRAY_BUFFER, this->vertices.size() * sizeof( Vertex ), &this->vertices[0], GL_STATIC_DRAW );

	glGenBuffers( 1, &this->ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof( GLuint ), &this->elements[0] , GL_STATIC_DRAW );

	this->mat = nullptr;

	glBindVertexArray( 0 );
}

StaticMesh::~StaticMesh()
{
	glDeleteBuffers( 1, &this->vbo );
	glDeleteBuffers( 1, &this->ebo );
	glDeleteVertexArrays( 1, &this->vao );
}

///////////////////////////////
///   Getters and Setters   ///
///////////////////////////////

GLuint StaticMesh::getVAO() const
{
	return this->vao;
}

const unsigned int StaticMesh::getNumElements() const
{
	return this->elements.size();
}

Material& StaticMesh::getMaterial() const
{
	return *this->mat;
}

// @TODO: this needs work! I need to figure out the proper use of VAOs
void StaticMesh::setMaterial( Material& _mat )
{
	mat = &_mat;

	// Bind the VAO
	glBindVertexArray( this->vao );
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

	// Set stuff
	GLuint posAttrib;
	posAttrib = glGetAttribLocation( mat->getID(), "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	GLint texAttrib = glGetAttribLocation( mat->getID(), "texcoord" );
	glEnableVertexAttribArray( texAttrib );
	glVertexAttribPointer( texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)sizeof( Vec3 ) );

	glBindVertexArray( 0 );
}