// StaticMesh.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/Render/StaticMesh.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(StaticMesh);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const String& path)
	: Super(path)
{
	// Generate buffers and upload data
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, Vertices.Size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.Size() * sizeof(uint32), &Elements[0], GL_STATIC_DRAW);

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

ResourceHandle<Material> StaticMesh::GetMaterial() const
{
	return _material;
}

void StaticMesh::SetMaterial(const ResourceHandle<Material>& material)
{
	_material = material;

	if (!_material.IsLoaded())
	{
		return;
	}

	// Bind the VAO
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Set stuff
	BufferID vPosition;
	vPosition = glGetAttribLocation(_material->GetID(), "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	BufferID vTexcoord = glGetAttribLocation(_material->GetID(), "vTexcoord");
	glEnableVertexAttribArray(vTexcoord);
	glVertexAttribPointer(vTexcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, U));

	BufferID vNormal = glGetAttribLocation(_material->GetID(), "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, I));

	glBindVertexArray(NULL);
}

void StaticMesh::Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const
{
	// Bind the mesh
	glBindVertexArray(_vao);

	// Bind the material
	this->GetMaterial()->Bind();

	// Upload the matrix to the GPU
	_material->UploadModelMatrix(orientation);
	_material->UploadViewMatrix(view);
	_material->UploadProjectionMatrix(perspective);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)Elements.Size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(NULL);
}