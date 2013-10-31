#include "Shader.h"
#include "headers.h"


Shader::Shader( string filename, GLenum INIT_type )
{
	//load source and type
	source = load( filename );
	type = INIT_type;

	//covert source to a c-string
	const char* temp_source = source.c_str();

	//Compile the shader
	id = glCreateShader( type );
	glShaderSource( id, 1, &temp_source, NULL );
	glCompileShader( id );

	//Check for errors
	if ( validate() )
	{
		std::cout << "Shader " << id << " compiled sucessfully" << std::endl;
	}
	else
	{
		std::cout << "Shader " << id << " could not compile" << std::endl;
	}
}


Shader::Shader()
{
	//Do nothing
}


Shader::~Shader()
{
	//Delete the shader
	glDeleteShader( id );
}


Shader::operator GLint()
{
	//For converting shader to GLint
	return id;
}


GLint Shader::validate()
{
	GLint status;
	glGetShaderiv( id, GL_COMPILE_STATUS, &status );
	return status;
}


GLint Shader::getId()
{
	return id;
}

GLenum Shader::getType()
{
	return type;
}


string Shader::load( string filename )
{
	std::ifstream ex_source;
	std::string line;
	std::string in_source = "";

	ex_source.open( filename );

	while ( std::getline( ex_source, line ) )
	{
		in_source += line;
		in_source += "\n";
	}

	ex_source.close();

	return in_source;
}