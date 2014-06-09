// Material.cpp

#include "Material.h"
#include "Shader.h"

////////////////////////
///   Constructors   ///

Material::Material( const Shader& _vertex, const Shader& _fragment )
{
	this->vertex = const_cast< Shader* >(&_vertex);
	this->fragment = const_cast< Shader* >(&_fragment);
	
	this->id = glCreateProgram();

	glAttachShader( this->id, this->vertex->getID() );
	glAttachShader( this->id, this->fragment->getID() );

	glBindFragDataLocation( this->id, 0, "outColor" );
	glLinkProgram( this->id );

	// get matrix location
	this->vModel = glGetUniformLocation( this->id, "vModel" );
	this->vView = glGetUniformLocation( this->id, "vView" );
	this->vProjection = glGetUniformLocation( this->id, "vProjection" );
	this->Time = glGetUniformLocation( this->id, "Time" );
}

Material::~Material()
{
	glDeleteProgram( this->id );
}

///////////////////////////////
///   Getters and Setters   ///

GLuint Material::getID() const
{
	return this->id;
}

Texture& Material::getTexture() const
{
	return *this->texture;
}

void Material::setTexture( const Texture& _TEX )
{
	this->texture = const_cast< Texture* >(&_TEX);
}

GLuint Material::getModelID() const
{
	return this->vModel;
}

GLuint Material::getViewID() const
{
	return this->vView;
}

GLuint Material::getProjectionID() const
{
	return this->vProjection;
}

GLuint Material::getTimeID() const
{
	return this->Time;
}