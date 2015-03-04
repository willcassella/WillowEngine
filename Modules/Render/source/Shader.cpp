// Shader.cpp

#include <Utility\TextFileReader.h>
#include <Utility\Console.h>
#include "glew.h"
#include "..\include\Render\shader.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Shader::Shader(const String& path)
	: Super(path)
{
	TextFileReader file(path);

	// Make sure the file opened correctly
	if (!file.FileOpen())
	{
		Console::Warning("Shader at '@' could not be opened", path);
		this->_id = NULL;
		return;
	}

	String source = file.Dump();

	// Identify the shader type and construct the shader
	String type = String::GetFileExtension(path);
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

	// Compile the shader
	const char* tempSource = source.Cstr();
	glShaderSource(_id, 1, &tempSource, nullptr);
	glCompileShader(_id);

	// Make sure the shader compiled successfully
	GLint compiled;
	glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLsizei length;
		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);

		GLchar* log = new GLchar[length + 1];
		glGetShaderInfoLog(_id, length, &length, log);
		Console::Error("Shader compilation failed: \"@\"", log);
		delete[] log;
	}

	Console::WriteLine("'@' loaded", path);
}

Shader::~Shader()
{
	glDeleteShader(this->_id);
}

///////////////////
///   Methods   ///

BufferID Shader::GetID() const
{
	return _id;
}