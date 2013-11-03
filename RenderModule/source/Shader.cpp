#include "Shader.h"
#include <string>

Shader::Shader( std::string _source, GLenum type )
{
	source = _source;
	const char* temp_source = source.c_str();
	id = glCreateShader( type );
	glShaderSource( id, 1, &temp_source, NULL );
	glCompileShader( id );
}

Shader::~Shader()
{
	glDeleteShader( id );
}

std::string Shader::basic_vert_source =
    "#version 150 core\n"
    "in vec2 position;"
    "in vec3 color;"
    "out vec3 Color;"
    "void main() {"
    "   Color = color;"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";

std::string Shader::basic_frag_source =
    "#version 150 core\n"
    "in vec3 Color;"
    "out vec4 outColor;"
    "void main() {"
    "   outColor = vec4(Color, 1.0);"
    "}";


//Shader Shader::basic_vert ( Shader::basic_vert_source, GL_VERTEX_SHADER );
//Shader Shader::basic_frag ( Shader::basic_frag_source, GL_FRAGMENT_SHADER );