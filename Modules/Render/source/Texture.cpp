// Texture.cpp

#include <Utility\Console.h>
#include <SOIL.h>
#include "glew.h"
#include "..\include\Render\Texture.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Texture::Texture(const String& path)
	: Super(path)
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

	int32 width, height;
	byte* image = SOIL_load_image(path.Cstr(), &width, &height, 0, SOIL_LOAD_RGB);

	if (!image)
	{
		Console::Warning("'@' could not be opened", path);
		SOIL_free_image_data(image);
		return;
	}

	// @TODO: Switch to FreeImage
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	Console::WriteLine("'@' loaded", path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->_id);
}

///////////////////
///   Methods   ///

BufferID Texture::GetID() const
{
	return this->_id;
}