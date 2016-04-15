// GLShader.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/GLRender/GLShader.h"

namespace willow
{
	////////////////////////
	///   Constructors   ///

	GLShader::GLShader(const Shader& shader)
	{
		// Identify the shader type and construct the shader
		switch (shader.get_shader_type())
		{
		case Shader::Type::Vertex_Shader:
			this->_id = glCreateShader(GL_VERTEX_SHADER);
			break;

		case Shader::Type::Fragment_Shader:
			this->_id = glCreateShader(GL_FRAGMENT_SHADER);
			break;

		case Shader::Type::Geometry_Shader:
			this->_id = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}

		// Compile the shader
		CString tempSource = shader.get_source().Cstr();
		glShaderSource(this->_id, 1, &tempSource, nullptr);
		glCompileShader(this->_id);

		// Make sure the shader compiled successfully
		GLint compiled;
		glGetShaderiv(this->_id, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei length;
			glGetShaderiv(this->_id, GL_INFO_LOG_LENGTH, &length);

			GLchar* log = new GLchar[length + 1];
			glGetShaderInfoLog(this->_id, length, &length, log);
			Console::Error("Shader compilation failed: \"@\"", log);
			delete[] log;
		}
	}

	GLShader::GLShader(const Path& path)
		: GLShader(Shader{ path })
	{
		// All done
	}

	GLShader::GLShader(GLShader&& move)
	{
		this->_id = move._id;
		move._id = 0;
	}

	GLShader::~GLShader()
	{
		glDeleteShader(this->_id);
	}
}
