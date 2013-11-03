#ifndef SHADER_H_
#define SHADER_H_

#include <GL\glew.h>
#include <string>

class Shader
{
public:
	Shader( std::string _source, GLenum type );
	~Shader();

	std::string source;
	
	GLuint id;

	static Shader basic_vert;
	static Shader basic_frag;
};

#endif