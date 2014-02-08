#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL\glew.h>

class Texture
{
public:
	Texture();
	Texture( const char* path );
	~Texture();

	void Load( const char* path );

	GLuint id;

private:

	bool loaded;
};

#endif