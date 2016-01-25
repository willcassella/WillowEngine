// GLStaticMesh.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/StaticMesh.h>
#include "GLPrimitive.h"

struct GLRENDER_API GLStaticMesh final : GLPrimitive
{
	////////////////////////
	///   Constructors   ///
public:

	/** Uploads the given Mesh asset to the GPU. */
	GLStaticMesh(GLRenderer& renderer, const StaticMesh& mesh);

	GLStaticMesh(GLStaticMesh&& move);
	~GLStaticMesh();

	///////////////////
	///   Methods   ///
public:

	void Bind() const;

	/** Returns the ID of the Vertex Array Object for this StaticMesh. */
	FORCEINLINE BufferID GetVao() const
	{
		return _vao;
	}

	/** Returns the Vertex Buffer Object for this StaticMesh. */
	FORCEINLINE BufferID GetVBO() const
	{
		return _vbo;
	}

	/** Returns the Element Buffer Object for this StaticMesh. */
	FORCEINLINE BufferID GetEBO() const
	{
		return _ebo;
	}

	/** Returns the number of elements in this Mesh. */
	FORCEINLINE uint32 GetNumElements()
	{
		return _numElements;
	}

	////////////////
	///   Data   ///
private:

	BufferID _vao;
	BufferID _vbo;
	BufferID _ebo;
	uint32 _numElements;
};
