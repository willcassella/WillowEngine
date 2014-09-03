// Material.cpp

#include "glew.h"
#include "..\include\Render\Material.h"
using namespace Render;

////////////////////////
///   Constructors   ///

Material::Material(Shader& _vertex, Shader& _fragment)
{
	this->vertex = &_vertex;
	this->fragment = &_fragment;
	
	this->id = glCreateProgram();

	glAttachShader(this->id, this->vertex->getID());
	glAttachShader(this->id, this->fragment->getID());

	glBindFragDataLocation(this->id, 0, "outColor");
	glLinkProgram(this->id);

	// get matrix location
	this->vModel = glGetUniformLocation(this->id, "vModel");
	this->vView = glGetUniformLocation( this->id, "vView" );
	this->vProjection = glGetUniformLocation( this->id, "vProjection" );
}

Material::~Material()
{
	glDeleteProgram( this->id );
}

///////////////////////////////
///   Getters and Setters   ///

BufferID Material::getID() const
{
	return this->id;
}

Texture& Material::getTexture() const
{
	return *this->texture;
}

void Material::setTexture(Texture& _texture)
{
	this->texture = &_texture;
}

BufferID Material::getModelID() const
{
	return this->vModel;
}

BufferID Material::getViewID() const
{
	return this->vView;
}

BufferID Material::getProjectionID() const
{
	return this->vProjection;
}