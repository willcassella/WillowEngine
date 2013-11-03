#include "Shader.h"
#include <string>

std::string basic_vert_source = "\
	\
	#version 150\n\
	\
	in vec2 position; \
	in vec3 color; \
	\
	out vec3 Color; \
	\
	void main() \
	{\
		Color = color;\
		gl_Position = vec4( position, 0.0, 1.0 );\
	}";

std::string basic_frag_source = "\
	\
	#version 150\n\
	\
	in vec3 Color; \
	\
	out vec4 outColor; \
	\
	void main() \
	{\
		outColor = vec4( Color, 1.0 ); \
	}";

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

Shader Shader::basic_vert ( basic_vert_source, GL_VERTEX_SHADER );
Shader Shader::basic_frag ( basic_frag_source, GL_FRAGMENT_SHADER );