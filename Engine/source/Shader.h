#ifndef SHADER_H_
#define SHADER_H_

#include <GL\glew.h>
#include <string>

class Shader
{
public:

	Shader();
	Shader( std::string _source, GLenum type );
	~Shader();


	//Load and unload shader to GPU
	void Load( std::string _source, GLenum type );
	void Unload();

	// Shader information
	GLuint id;

	static std::string basic_vert_source;
	static std::string basic_frag_source;

private:

	std::string source;

	//Holds whether shader has been loaded to GPU
	bool loaded;
};

#endif