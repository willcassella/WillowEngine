#include "Material.h"
#include "Shader.h"

Material::Material( Shader *_vertex, Shader *_fragment )
{
	vertex = _vertex;
	fragment = _fragment;
	
	id = glCreateProgram();
	glAttachShader( id, vertex->id );
	glAttachShader( id, fragment->id );

	glBindFragDataLocation( id, 0, "outColor" );
	glLinkProgram( id );
}

Material::~Material()
{
	glDeleteProgram( id );
}

Material Material::basic ( &Shader::basic_vert, &Shader::basic_frag );