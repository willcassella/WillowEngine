// GLShader.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/GLRender/GLShader.h"

////////////////////////
///   Constructors   ///

GLShader::GLShader(const TextFile& sourceFile)
{
	String source = sourceFile.DumpLines();

	// Identify the shader type and construct the shader
	String type = String::GetFileExtension(sourceFile.GetPath());
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
}

Shader::~Shader()
{
	glDeleteShader(this->_id);
}
