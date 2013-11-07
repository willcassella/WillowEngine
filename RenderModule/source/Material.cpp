#include "Material.h"
#include "Shader.h"

Material::Material()
{
	loaded = false;
}

Material::Material( Shader *_vertex, Shader *_fragment )
{
	vertex = _vertex;
	fragment = _fragment;
	
	id = glCreateProgram();

	glAttachShader( id, vertex->id );
	glAttachShader( id, fragment->id );

	glBindFragDataLocation( id, 0, "outColor" );
	glLinkProgram( id );

	// get matrix locations
	model = glGetUniformLocation( id, "model" );
	view = glGetUniformLocation( id, "view" );
	proj = glGetUniformLocation( id, "proj" );


	//TODO: find a better place for this
	glUseProgram( id );

	loaded = true;
}

Material::~Material()
{
	Unload();
}

void Material::Load( Shader *_vertex, Shader *_fragment )
{
	vertex = _vertex;
	fragment = _fragment;
	
	if( !loaded )
		id = glCreateProgram();

	if( loaded )
	{
		glDetachShader( id, vertex->id );
		glDetachShader( id, fragment->id );
	}

	glAttachShader( id, vertex->id );
	glAttachShader( id, fragment->id );

	glBindFragDataLocation( id, 0, "outColor" );
	glLinkProgram( id );

	model = glGetUniformLocation( id, "model" );
	view = glGetUniformLocation( id, "view" );
	proj = glGetUniformLocation( id, "proj" );

	//TODO: find a better place for this
	glUseProgram( id );

	loaded = true;
}

void Material::Unload()
{
	if( loaded )
		glDeleteProgram( id );

	loaded = false;
}