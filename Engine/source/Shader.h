#ifndef SHADER_H_
#define SHADER_H_

#include <GL\glew.h>
#include <string>

#include "object.h"

class Shader : public object
{
	REGISTER(Shader);

	////////////////////////
	///   Constructors   ///

	Shader(std::string _source, GLenum type);
	~Shader();

	////////////////
	///   Data   ///
private:

	GLuint id;
	std::string source;

	///////////////////////////////
	///   Getters and Setters   ///
public:

	GLuint getID() const;

	//////////////////////////
	///   Static Members   ///
public:

	static std::string basic_vert_source;
	static std::string basic_frag_source;
};

#endif