// Texture.cpp

#include <Utility\Console.h>
#include <FreeImage.h>
#include "glew.h"
#include "..\include\Render\Texture.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Texture::Texture(const String& path)
	: Super(path)
{
	// Open the file
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.Cstr());
	FIBITMAP* image = FreeImage_Load(format, path.Cstr(), 0);

	if (!image)
	{
		Console::Warning("'@' could not be opened", path);
		this->_id = 0;
		return;
	}

	FIBITMAP* temp = image;
	image = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);

	int32 width = FreeImage_GetWidth(image);
	int32 height = FreeImage_GetHeight(image);

	// Create and bind the buffer
	glGenTextures(1, &this->_id);
	glBindTexture(GL_TEXTURE_2D, this->_id);

	// Set wrapping parameters to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set filtering parameters, I should learn more about this
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, FreeImage_GetBits(image));

	// Done using the image
	FreeImage_Unload(image);

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