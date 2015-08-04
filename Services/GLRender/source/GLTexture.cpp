// GLTexture.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "..\include\Render\Texture.h"

////////////////////////
///   Constructors   ///

Texture::Texture(const Image& image)
	: Super(image)
{
	// Create and bind the buffer
	glGenTextures(1, &this->_id);
	glBindTexture(GL_TEXTURE_2D, this->_id);

	// Set wrapping parameters to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set filtering parameters, I should learn more about this
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	OnReload();
}

Texture::~Texture()
{
	OnUnload();
}

///////////////////
///   Methods   ///

void Texture::OnUnload()
{
	glDeleteTextures(1, &this->_id);
}

void Texture::OnReload()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GetResource().GetWidth(), GetResource().GetHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, GetResource().GetBitmap());
}