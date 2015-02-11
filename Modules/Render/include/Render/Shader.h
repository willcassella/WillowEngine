// Shader.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/TextFile.h>
#include "Render.h"

// @TODO: Prefer composition over inheritance
class RENDER_API Shader : public TextFile
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TextFile);

	////////////////////////
	///   Constructors   ///
public:

	Shader(const String& path);
	Shader(const Shader& copy) = delete;
	Shader(Shader&& move) = delete;
	~Shader() override;

	///////////////////
	///   Methods   ///
public:

	BufferID GetID() const;

	/////////////////////
	///   Operators   ///
public:

	Shader& operator=(const Shader& copy) = delete;
	Shader& operator=(Shader&& move) = delete;

	////////////////
	///   Data   ///
private:

	BufferID _id;
};