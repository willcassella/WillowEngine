// StaticMesh.cpp

#include <fstream>
#include <iostream>
#include "glew.h"
#include "..\include\Render\Vertex.h"
#include "..\include\Render\StaticMesh.h"
using namespace Render;

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const Willow::String& path)
{
	loadBinaryModel(path, &this->vertices, &this->elements);

	// Generate buffers and upload data
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elements.size() * sizeof(GLuint), &this->elements[0] , GL_STATIC_DRAW);

	this->mat = nullptr;

	glBindVertexArray(0);
}

StaticMesh::~StaticMesh()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
	glDeleteVertexArrays(1, &this->vao);
}

///////////////////
///   Methods   ///

void StaticMesh::render(const Math::Mat4& orientation, const Math::Mat4& view, const Math::Mat4& perspective) const
{
	// Bind the mesh
	glBindVertexArray(this->vao);

	// Bind the material
	glUseProgram(this->getMaterial().getID());

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, this->getMaterial().getTexture().getID());

	// Upload the matrix to the GPU
	glUniformMatrix4fv(this->getMaterial().getModelID(), 1, GL_FALSE, orientation[0]);
	glUniformMatrix4fv(this->getMaterial().getViewID(), 1, GL_FALSE, view[0]);
	glUniformMatrix4fv(this->getMaterial().getProjectionID(), 1, GL_FALSE, perspective[0]);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)this->getNumElements(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

uint StaticMesh::getNumElements() const
{
	return this->elements.size();
}

Material& StaticMesh::getMaterial() const
{
	return *this->mat;
}

void StaticMesh::setMaterial(Material& _mat)
{
	mat = &_mat;

	// Bind the VAO
	glBindVertexArray( this->vao );
	glBindBuffer( GL_ARRAY_BUFFER, this->vbo );

	// Set stuff
	BufferID vPosition;
	vPosition = glGetAttribLocation( mat->getID(), "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	BufferID vTexcoord = glGetAttribLocation( mat->getID(), "vTexcoord" );
	glEnableVertexAttribArray( vTexcoord );
	glVertexAttribPointer( vTexcoord, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), (void*)sizeof( Math::Vec3 ) );

	BufferID vNormal = glGetAttribLocation( mat->getID(), "vNormal" );
	glEnableVertexAttribArray( vNormal );
	glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_TRUE, sizeof( Vertex ), (void*)(sizeof( Math::Vec3) + sizeof( Math::Vec2 ) ));

	glBindVertexArray( 0 );
}

// @TODO: this needs to be refactored
bool StaticMesh::loadBinaryModel(const Willow::String& path, Willow::Array<Vertex>* out_vertices, Willow::Array<BufferID>* out_elements)
{
	// Attempt to open the file
	std::ifstream input;
	input.open(path, std::ios::binary | std::ios::in);

	// Make sure the file opened sucessfully
	if (!input.is_open()) 
	{
		std::cout << path;
		std::cout << " could not be opened!\n";
		return false;
	}

	// Get the number of vertices
	int num_verts;
	input.read((char*)&num_verts, sizeof(int));

	// Add all the vertices
	for (int i = 0; i < num_verts; i++) 
	{
		Vertex newVert;
		input.read((char*)&newVert, sizeof(Vertex));
		out_vertices->add(newVert);
	}

	// Get the number of elements
	int num_elems;
	input.read((char*)&num_elems, sizeof(int));

	// Add all the elements
	for (int i = 0; i < num_elems; i++) 
	{
		BufferID newElem;
		input.read((char*)&newElem, sizeof(unsigned int));
		out_elements->add(newElem);
	}

	// Close the file
	input.close();

	return true;
}