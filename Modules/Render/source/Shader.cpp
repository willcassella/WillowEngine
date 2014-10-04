// Shader.cpp

#include <fstream>
#include <string>
#include <Utility\Console.h>
#include "glew.h"
#include "..\include\Render\shader.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Shader::Shader(const String& path)
	: Super(path)
{
	// Aggregate the shader source code
	std::ifstream file(path.Cstr());

	// Make sure the file opened correctly
	if (!file.is_open())
	{
		Console::Warning("'@' could not be opened", path);
		this->_id = NULL;
		return;
	}

	std::string source;
	std::string line;
	while (getline(file, line))
	{
		source += line + '\n';
	}

	// Identify the shader type
	String type = path.GetFileExtension();

	if (type == "vert")
	{
		this->_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == "frag")
	{
		this->_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (type == "geom")
	{
		this->_id = glCreateShader(GL_GEOMETRY_SHADER);
	}

	const char* tempSource = source.c_str();
	glShaderSource(_id, 1, &tempSource, nullptr);
	glCompileShader(_id);

	Console::WriteLine("'@' loaded", path);
}

Shader::~Shader()
{
	glDeleteShader(this->_id);
}

/////////////////////
///   Operators   ///

Shader::operator BufferID() const
{
	return this->_id;
}