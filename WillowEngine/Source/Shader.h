#ifndef SHADER_H_
#define SHADER_H_

#include "headers.h"

class Shader
{
private:
	std::string source;
	GLenum type;
	GLint id;
	std::string load( std::string filename );

public:
	//Constructors
	Shader( std::string filename, GLenum INIT_type );
	Shader();
	//Destructor
	~Shader();
	//Cast to GLint
	operator GLint();
	GLint validate();
	GLint getId();
	GLenum getType();
};

#endif