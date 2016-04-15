// GLTexture.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/GLRender/GLTexture.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	GLTexture::GLTexture(const Texture& image)
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

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.get_width(), image.get_height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.get_bitmap());
	}

	GLTexture::GLTexture(GLTexture&& move)
	{
		this->_id = move._id;
		move._id = 0;
	}

	GLTexture::~GLTexture()
	{
		glDeleteTextures(1, &this->_id);
	}
}
