#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL\glew.h>

#include "object.h"

class Texture : public object
{
	REGISTER(Texture);

	////////////////////////
	///   Constructors   ///

	Texture(const std::string& path);
	~Texture();

	////////////////
	///   Data   ///
private:

	GLuint id;

	///////////////////////////////
	///   Getters and Setters   ///
public:

	GLuint getID() const;
};

#endif