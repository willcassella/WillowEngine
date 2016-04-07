// GLStaticMesh.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Containers/Array.h>
#include "glew.h"
#include "../include/GLRender/GLStaticMesh.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	GLStaticMesh::GLStaticMesh(GLRenderSystem& renderer, const StaticMesh& mesh)
		: GLPrimitive(renderer)
	{
		_numVertices = static_cast<GLInteger>(mesh.Vertices.Size());

		// Generate buffers and upload data
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh.Vertices.Size() * sizeof(StaticMesh::Vertex), &mesh.Vertices[0], GL_STATIC_DRAW);

		// Setup vertex specification
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(StaticMesh::Vertex), nullptr); // "vPosition" attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(StaticMesh::Vertex), (void*)offsetof(StaticMesh::Vertex, UV)); // "vTexCoord" attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(StaticMesh::Vertex), (void*)offsetof(StaticMesh::Vertex, Normal)); // "vNormal" attribute

		glBindVertexArray(0);
	}

	GLStaticMesh::GLStaticMesh(GLStaticMesh&& move)
		: GLPrimitive(move.GetRenderer())
	{
		_vao = move._vao;
		_vbo = move._vbo;
		_numVertices = move._numVertices;

		move._vao = 0;
		move._vbo = 0;
		move._numVertices = 0;
	}

	GLStaticMesh::~GLStaticMesh()
	{
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	///////////////////
	///   Methods   ///

	void GLStaticMesh::Bind() const
	{
		glBindVertexArray(_vao);
	}
}
