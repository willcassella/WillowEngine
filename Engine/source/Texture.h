#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL\glew.h>

class Texture
{
	////////////////
	///   Data   ///
	////////////////
private:

	GLuint id;

	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	Texture( const std::string& path );
	~Texture();

	///////////////////////////////
	///   Getters and Setters   ///
	///////////////////////////////
public:

	GLuint getID() const;
};

#endif