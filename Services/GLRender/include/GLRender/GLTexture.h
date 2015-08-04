// GLTexture.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Texture.h>
#include "GLRender.h"

struct GLRENDER_API GLTexture final
{
	////////////////////////
	///   Constructors   ///
public:

	GLTexture(const Texture& texture);
	GLTexture(const GLTexture& copy) = delete;
	GLTexture(GLTexture&& move);
	~GLTexture() override;

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
