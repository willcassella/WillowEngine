// GLMaterial.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Material.h>
#include "GLShader.h"
#include "GLTexture.h"

struct GLRENDER_API GLMaterial final
{
	////////////////////////
	///   Constructors   ///
public:

	GLMaterial(const Material& material);
	~GLMaterial() override;

	//////////////////
	///   Fields   ///
public:

	Shader* VertexShader;
	Shader* FragmentShader;
	Table<String, Texture*> Textures;

	///////////////////
	///   Methods   ///
public:

	// @TODO: This needs some serious work. Once I have a more finalized rendering pipeline set up I'll do some major refactoring here
	void Compile();
	void Bind() const;
	BufferID GetID() const;
	void UploadModelMatrix(const Mat4& matrix) const;
	void UploadViewMatrix(const Mat4& matrix) const;
	void UploadProjectionMatrix(const Mat4& matrix) const;

	////////////////
	///   Data   ///
private:

	BufferID _id;
	BufferID _model;
	BufferID _view;
	BufferID _projection;
};
