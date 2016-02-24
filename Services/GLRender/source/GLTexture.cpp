// GLTexture.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/GLRender/GLTexture.h"

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	GLTexture::GLTexture(GLRenderer& renderer, const Texture& image)
		: GLPrimitive(renderer)
	{
		// Create and bind the buffer
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);

		// Set wrapping parameters to repeat
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set filtering parameters, I should learn more about this
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.GetWidth(), image.GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.GetBitmap());
	}

	GLTexture::GLTexture(GLTexture&& move)
		: GLPrimitive(move.GetRenderer())
	{
		_id = move._id;
		move._id = 0;
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &_id);
	}
}
