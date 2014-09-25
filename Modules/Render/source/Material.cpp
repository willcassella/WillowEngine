// Material.cpp

#include "glew.h"
#include "..\include\Render\Material.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Material::Material()
{
	this->_id = glCreateProgram();
}

Material::~Material()
{
	glDeleteProgram(_id);
}

///////////////////
///   Methods   ///

void Material::Compile()
{
	glAttachShader(_id, *VertexShader);
	glAttachShader(_id, *FragmentShader);
	glLinkProgram(_id);

	glBindFragDataLocation(_id, 0, "outColor");

	this->_vModel = glGetUniformLocation(_id, "vModel");
	this->_vView = glGetUniformLocation(_id, "vView");
	this->_vProjection = glGetUniformLocation(_id, "vProjection");

	glDetachShader(_id, *VertexShader);
	glDetachShader(_id, *FragmentShader);
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
	}
}

void Material::UploadModelMatrix(const Mat4& matrix)
{
	glUniformMatrix4fv(_vModel, 1, GL_FALSE, matrix[0]);
}

void Material::UploadViewMatrix(const Mat4& matrix)
{
	glUniformMatrix4fv(_vView, 1, GL_FALSE, matrix[0]);
}

void Material::UploadProjectionMatrix(const Mat4& matrix)
{
	glUniformMatrix4fv(_vProjection, 1, GL_FALSE, matrix[0]);
}

/////////////////////
///   Operators   ///

Material::operator BufferID() const
{
	return _id;
}