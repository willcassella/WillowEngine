// GLStaticMesh.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Containers/Array.h>
#include "glew.h"
#include "..\include\GLRender\GLStaticMesh.h"

////////////////////////
///   Constructors   ///

GLStaticMesh::GLStaticMesh(const StaticMesh& mesh)
{
	this->_numElements = elements.Size();

	// Generate buffers and upload data
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.Size() * sizeof(uint32), &elements[0] , GL_STATIC_DRAW);

	// Setup vertex specification
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // "vPosition" attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, U)); // "vTexCoord" attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, I)); // "vNormal" attribute

	glBindVertexArray(NULL);
}

StaticMesh::~StaticMesh()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

///////////////////
///   Methods   ///

void StaticMesh::Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const
{
	// Bind the mesh
	glBindVertexArray(_vao);

	// Bind the material
	_mat->Bind();

	// Upload the matrix to the GPU
	_mat->UploadModelMatrix(orientation);
	_mat->UploadViewMatrix(view);
	_mat->UploadProjectionMatrix(perspective);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)_numElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(NULL);
}

const ResourcePtr<Material>& StaticMesh::GetMaterial() const
{
	return _mat;
}

void StaticMesh::SetMaterial(const ResourcePtr<Material>& material)
{
	_mat = material;
}
