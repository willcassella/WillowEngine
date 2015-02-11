// Material.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Math/Mat4.h>
#include <Resource/ResourceHandle.h>
#include "Shader.h"
#include "Texture.h"

// @TODO: This should not inherit from TextFile
class RENDER_API Material : public TextFile
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TextFile);

	////////////////////////
	///   Constructors   ///
public:

	Material(const String& path);
	Material(const Material& copy) = delete;
	Material(Material&& move) = delete;
	~Material() override;

	//////////////////
	///   Fields   ///
public:

	ResourceHandle<Shader> VertexShader;
	ResourceHandle<Shader> FragmentShader;
	Table<String, ResourceHandle<Texture>> Textures;

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

	/////////////////////
	///   Operators   ///
public:

	Material& operator=(const Material& copy) = delete;
	Material& operator=(Material&& move) = delete;

	////////////////
	///   Data   ///
private:

	BufferID _id;
	BufferID _vModel;
	BufferID _vView;
	BufferID _vProjection;
};