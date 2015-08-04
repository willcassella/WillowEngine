// GLStaticMesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/StaticMesh.h>
#include "GLMaterial.h"

class RENDER_API StaticMesh : public ResourceConsumer
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(ResourceConsumer)

	////////////////////////
	///   Constructors   ///
public:

	StaticMesh(const Mesh& mesh);
	~StaticMesh() override;

	///////////////////
	///   Methods   ///
public:

	/** Render the mesh at a specific orientation, view, and perspective */
	void Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const;
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
