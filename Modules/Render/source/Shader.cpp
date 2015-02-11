// Shader.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/Render/shader.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Shader);

////////////////////////
///   Constructors   ///

Shader::Shader(const String& path)
	: Super(path)
{
	// Identify the shader type
	String type = String::GetFileExtension(path);

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

	String source = DumpLines();
	const char* tempSource = source.Cstr();
	glShaderSource(_id, 1, &tempSource, nullptr);
	glCompileShader(_id);
}

Shader::~Shader()
{
	glDeleteShader(_id);
}

///////////////////
///   Methods   ///

BufferID Shader::GetID() const
{
	return _id;
}