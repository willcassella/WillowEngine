// GLShader.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Shader.h>
#include "GLPrimitive.h"

struct GLRENDER_API GLShader final : GLPrimitive
{
	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a GLShader corresponding to a Shader asset. */
	GLShader(GLRenderer& renderer, const Shader& shader);

	/** Constructs a GLShader using a file */
	GLShader(GLRenderer& renderer, const Path& path);

	GLShader(GLShader&& move);
	~GLShader();

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE BufferID GetID() const
	{
		return _id;
	}

	////////////////
	///   Data   ///
private:

	BufferID _id;
};
