// Texture.cpp

#include <string>
#include <SOIL.h>
#include "Texture.h"

////////////////////////
///   Constructors   ///
////////////////////////

Texture::Texture( const std::string& path )
{
	// Create and bind the buffer
	glGenTextures( 1, &this->id );
	glBindTexture( GL_TEXTURE_2D, this->id );

	// Set wrapping paremeters to repeat
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	// Set filtering parameters, I should learn more about this
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	int width, height;
	unsigned char* image = SOIL_load_image( path.c_str(), &width, &height, 0, SOIL_LOAD_RGB );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
	SOIL_free_image_data( image );
}

Texture::~Texture()
{
	glDeleteTextures( 1, &this->id );
}

///////////////////////////////
///   Getters and Setters   ///
///////////////////////////////

GLuint Texture::getID() const
{
	return this->id;
}