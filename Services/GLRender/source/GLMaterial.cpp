// GLMaterial.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Console.h>
#include "glew.h"
#include "..\include\Render\Material.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Material);

////////////////////////
///   Constructors   ///

Material::Material(const TextFile& file)
	: Super(file)
{
	for (const auto& line : file.GetLines())
	{
		if (line == "Shaders:")
		{
			for (file.GetNextLine(line); !line.IsNullOrEmpty(); file.GetNextLine(line))
			{
				auto shader = String::ParseEquality(line);

				if (shader.First == "VertexShader")
				{
					this->VertexShader = shader.Second;
				}
				else if (shader.First == "FragmentShader")
				{
					this->FragmentShader = shader.Second;
				}
			}
		}
		else if (line == "Textures:")
		{
			for (file.GetNextLine(line); !line.IsNullOrEmpty(); file.GetNextLine(line))
			{
				auto texture = String::ParseEquality(line);

				this->Textures[texture.First] = texture.Second;
			}
		}
	}

	this->_id = glCreateProgram();
	this->Compile();
}

Material::~Material()
{
	glDeleteProgram(_id);
}

///////////////////
///   Methods   ///

void Material::Compile()
{
	glAttachShader(_id, VertexShader->GetID());
	glAttachShader(_id, FragmentShader->GetID());
	glBindAttribLocation(_id, 0, "vPosition");
	glBindAttribLocation(_id, 1, "vTexCoord");
	glBindAttribLocation(_id, 2, "vNormal");
	glLinkProgram(_id);

	// Make sure program successfully linked
	GLint linked;
	glGetProgramiv(_id, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

		GLchar* log = new GLchar[length + 1];
		glGetProgramInfoLog(_id, length, &length, log);
		Console::WriteLine("Material compilation failed: \"@\"", log);
		delete[] log;
	}

	_model = glGetUniformLocation(_id, "model");
	_view = glGetUniformLocation(_id, "view");
	_projection = glGetUniformLocation(_id, "projection");

	glDetachShader(_id, VertexShader->GetID());
	glDetachShader(_id, FragmentShader->GetID());
}

void Material::Bind() const
{
	glUseProgram(_id);

	uint32 texIndex = 0;
	for (const auto& i : Textures)
	{
		glActiveTexture(GL_TEXTURE0 + texIndex);
		glBindTexture(GL_TEXTURE_2D, i.Second->GetID());

		glUniform1i(glGetUniformLocation(_id, i.First.Cstr()), texIndex);
		++texIndex;
	}
}

BufferID Material::GetID() const
{
	return _id;
}

void Material::UploadModelMatrix(const Mat4& matrix) const
{
	glUniformMatrix4fv(_model, 1, GL_FALSE, matrix[0]);
}

void Material::UploadViewMatrix(const Mat4& matrix) const
{
	glUniformMatrix4fv(_view, 1, GL_FALSE, matrix[0]);
}

void Material::UploadProjectionMatrix(const Mat4& matrix) const
{
	glUniformMatrix4fv(_projection, 1, GL_FALSE, matrix[0]);
}