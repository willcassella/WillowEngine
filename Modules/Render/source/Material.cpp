// Material.cpp

#include <Utility\TextFileReader.h>
#include <Utility\Console.h>
#include "glew.h"
#include "..\include\Render\Material.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Material::Material(const String& path)
	: Super(path)
{
	TextFileReader file(path);

	if (!file.FileOpen())
	{
		Console::Warning("Material at '@' could not be loaded", path);
		return;
	}

	String line;
	while (file.GetNextLine(line))
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