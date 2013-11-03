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

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	//TODO: find a better place for this
	GLint posAttrib = glGetAttribLocation( id, "position" );
    glEnableVertexAttribArray( posAttrib );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0 );

    GLint colAttrib = glGetAttribLocation( id, "color" );
    glEnableVertexAttribArray( colAttrib );
    glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)) );
}

Material::~Material()
{
	glDeleteProgram( id );
}

//Material Material::basic ( &Shader::basic_vert, &Shader::basic_frag );