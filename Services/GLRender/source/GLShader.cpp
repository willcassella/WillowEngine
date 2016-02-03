// GLShader.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/GLRender/GLShader.h"

////////////////////////
///   Constructors   ///

GLShader::GLShader(GLRenderer& renderer, const Shader& shader)
	: GLPrimitive(renderer)
{
	// Identify the shader type and construct the shader
	String type = shader.GetPath().GetFileExtension();
	if (type == "vert")
	{
		_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == "frag")
	{
		_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (type == "geom")
	{
		_id = glCreateShader(GL_GEOMETRY_SHADER);
	}

	// Compile the shader
	CString tempSource = shader.GetSource().Cstr();
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

GLShader::GLShader(GLRenderer& renderer, const Path& path)
	: GLShader(renderer, Shader(path))
{
	// All done
}

GLShader::GLShader(GLShader&& move)
	: GLPrimitive(move.GetRenderer())
{
	_id = move._id;
	move._id = 0;
}

GLShader::~GLShader()
{
	glDeleteShader(this->_id);
}
