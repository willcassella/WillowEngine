// Material.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/Render/Material.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Material);

////////////////////////
///   Constructors   ///

Material::Material(const String& path)
	: Super(path)
{
	bool shaders = false;
	bool textures = false;

	for (const String& line : GetLines())
	{
		if (line == "Shaders:")
		{
			shaders = true;
			textures = false;
			continue;
		}
		else if (line == "Textures:")
		{
			shaders = false;
			textures = true;
			continue;
		}

		if (shaders)
		{
			Pair<String, String> pair;
			String::Parse(line, "@ = @", pair.First, pair.Second);

			if (pair.First == "VertexShader")
			{
				VertexShader = pair.Second;
			}
			else if (pair.First == "FragmentShader")
			{
				FragmentShader = pair.Second;
			}
		}
		else if (textures)
		{
			Pair<String, String> pair;
			String::Parse(line, "@ = @", pair.First, pair.Second);

			Textures[pair.First] = pair.Second;
		}
	}

	_id = glCreateProgram();
	Compile();
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
	glLinkProgram(_id);

	glBindFragDataLocation(_id, 0, "outColor");

	_vModel = glGetUniformLocation(_id, "vModel");
	_vView = glGetUniformLocation(_id, "vView");
	_vProjection = glGetUniformLocation(_id, "vProjection");

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
	glUniformMatrix4fv(_vModel, 1, GL_FALSE, matrix[0]);
}

void Material::UploadViewMatrix(const Mat4& matrix) const
{
	glUniformMatrix4fv(_vView, 1, GL_FALSE, matrix[0]);
}

void Material::UploadProjectionMatrix(const Mat4& matrix) const
{
	glUniformMatrix4fv(_vProjection, 1, GL_FALSE, matrix[0]);
}