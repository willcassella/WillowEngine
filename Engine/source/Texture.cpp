#include "Texture.h"

#include <SOIL.h>

Texture::Texture()
{
	loaded = false;
}

Texture::Texture( const char* path )
{
	// Create and bind the buffer
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );

	// Set wrapping paremeters to repeat
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	// Set filtering parameters, I should learn more about this
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	int width, height;
	unsigned char* image = SOIL_load_image( path, &width, &height, 0, SOIL_LOAD_RGB );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	loaded = true;
}

Texture::~Texture()
{
	//Delete the texture
}

void Texture::Load( const char* path )
{
	//do nothing
}