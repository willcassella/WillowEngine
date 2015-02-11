// Texture.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/Render/Texture.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Texture);

////////////////////////
///   Constructors   ///

Texture::Texture(const String& path)
	: Super(path)
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetWidth(), GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, GetBitmap());

	// @TODO: Discard FreeImage instance of image (since it now exists on the GPU)
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

///////////////////
///   Methods   ///

BufferID Texture::GetID() const
{
	return _id;
}