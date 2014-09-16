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

BufferID Material::GetModelID() const
{
	return _vModel;
}

BufferID Material::GetViewID() const
{
	return _vView;
}

BufferID Material::GetProjectionID() const
{
	return _vProjection;
}

/////////////////////
///   Operators   ///

Material::operator BufferID() const
{
	return _id;
}