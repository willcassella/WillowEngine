// GLTexture.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Assets/Texture.h>
#include "GLPrimitive.h"

struct GLRENDER_API GLTexture final : GLPrimitive
{
	////////////////////////
	///   Constructors   ///
public:

	/** Creates an OpenGL texture from the corresponding Texture asset. */
	GLTexture(GLRenderer& renderer, const Texture& texture);

	GLTexture(GLTexture&& move);
	~GLTexture();

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
