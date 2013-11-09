#include "Texture.h"

#include <SOIL.h>

Texture::Texture()
{
	loaded = false;
}

Texture::Texture( const char* path )
{
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	int width, height;
	unsigned char* image = SOIL_load_image( path, &width, &height, 0, SOIL_LOAD_RGB );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

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