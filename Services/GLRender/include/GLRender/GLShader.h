// GLShader.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Shader.h>
#include "GLRender.h"

struct GLRENDER_API GLShader final
{
	////////////////////////
	///   Constructors   ///
public:

	GLShader(const Shader& shader);
	GLShader(const GLShader& copy) = delete;
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
