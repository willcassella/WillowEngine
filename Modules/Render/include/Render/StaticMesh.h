// StaticMesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Mesh.h>
#include "Material.h"

// @TODO: This should not inherit from MeshFile
class RENDER_API StaticMesh : public Mesh
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Mesh);

	////////////////////////
	///   Constructors   ///
public:

	StaticMesh(const String& path);
	StaticMesh(const StaticMesh& copy) = delete;
	StaticMesh(StaticMesh&& move) = delete;
	~StaticMesh() override;

	///////////////////
	///   Methods   ///
public:
	
	/** Get the material for this mesh */
	ResourceHandle<Material> GetMaterial() const;

	/** Sets the material for this mesh */
	void SetMaterial(const ResourceHandle<Material>& material);

	/** Render the mesh at a specific orientation, view, and perspective */
	void Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const;

	/////////////////////
	///   Operators   ///
public:

	StaticMesh& operator=(const StaticMesh& copy) = delete;
	StaticMesh& operator=(StaticMesh&& move) = delete;

	////////////////
	///   Data   ///
private:

	BufferID _vao;
	BufferID _vbo;
	BufferID _ebo;
	ResourceHandle<Material> _material;
};