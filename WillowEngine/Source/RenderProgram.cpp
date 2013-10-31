#include "headers.h"
#include "RenderProgram.h"

RenderProgram::RenderProgram()
{
	//id = glCreateProgram();
}

RenderProgram::RenderProgram( Shader INIT_VertShader, Shader INIT_FragShader )
{
	//Create the program
	id = glCreateProgram();

	//Attatch vertex and fragment shaders
	glAttachShader( getId(), INIT_VertShader );
	glAttachShader( getId(), INIT_FragShader );

	//Limit it to one buffer
	glBindFragDataLocation( getId(), 0, "outColor" );

	//Link Program
	glLinkProgram( getId() );
}

RenderProgram::RenderProgram( Shader INIT_VertShader, Shader INIT_FragShader, Shader INIT_GeoShader )
{
	//Create the program
	id = glCreateProgram();

	//Attatch vertex, fragment, and geometry shaders
	glAttachShader( getId(), INIT_VertShader );
	glAttachShader( getId(), INIT_FragShader );
	glAttachShader( getId(), INIT_GeoShader );

	//Link Program
	glLinkProgram( getId() );
}

RenderProgram::~RenderProgram()
{
	glDeleteProgram( getId() );
	VertShader.~Shader();
	FragShader.~Shader();
	GeoShader.~Shader();
}

RenderProgram::operator GLint()
{
	return getId();
}

void RenderProgram::init()
{
	id = glCreateProgram();
}

void RenderProgram::compile()
{
	glLinkProgram( getId() );
}

void RenderProgram::use()
{
	glUseProgram( getId() );
}

GLint RenderProgram::getId()
{
	return id;
}

void RenderProgram::addShader( Shader shader )
{
	if( shader.getType() == GL_VERTEX_SHADER )
	{
		VertShader = shader;
		glAttachShader( getId(), VertShader );
	}
	else if( shader.getType() == GL_FRAGMENT_SHADER )
	{
		FragShader = shader;
		glAttachShader( getId(), FragShader );
	}
	else if( shader.getType() == GL_GEOMETRY_SHADER )
	{
		GeoShader = shader;
		glAttachShader( getId(), GeoShader );
	}
}