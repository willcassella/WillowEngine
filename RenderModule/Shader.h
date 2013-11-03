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

	static std::string basic_vert_source;
	static std::string basic_frag_source;

	//static Shader basic_vert;
	//static Shader basic_frag;
};

#endif