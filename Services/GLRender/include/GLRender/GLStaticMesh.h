// GLStaticMesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/StaticMesh.h>
#include "GLMaterial.h"

struct GLRENDER_API GLStaticMesh final
{
	////////////////////////
	///   Constructors   ///
public:

	GLStaticMesh(const StaticMesh& mesh);
	GLStaticMesh(GLStaticMesh&& move);
	~GLStaticMesh();

	///////////////////
	///   Methods   ///
public:

	/** Render the mesh at a specific orientation, view, and perspective */
	const Material& GetMaterial() const;
	void SetMaterial(const Material& material);

	////////////////
	///   Data   ///
private:

	BufferID _vao;
	BufferID _vbo;
	BufferID _ebo;
	uint32 _numElements;
	Material* _mat;
};
