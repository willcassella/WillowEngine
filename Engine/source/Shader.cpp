#include "Shader.h"
#include <string>

////////////////////////
///   Constructors   ///
////////////////////////

Shader::Shader( std::string _source, GLenum type )
{
	this->source = _source;
	const char* temp_source = source.c_str();

	this->id = glCreateShader( type );
	glShaderSource( this->id, 1, &temp_source, NULL );
	glCompileShader( this->id );
}

Shader::~Shader()
{
	glDeleteShader( this->id );
}

///////////////////////////////
///   Getters and Setters   ///
///////////////////////////////

GLuint Shader::getID() const
{
	return this->id;
}

//////////////////////////
///   Static Members   ///
//////////////////////////

std::string Shader::basic_vert_source =
    "#version 150 core\n"
    "in vec3 position;"
    "in vec2 texcoord;"
	"out vec2 Texcoord;"
	"uniform mat4 clipspace;"
    "void main() {"
	"   gl_Position = clipspace * vec4( position, 1.0 );"
	"	Texcoord = vec2(texcoord.x, 1.0 - texcoord.y);"
    "}";

std::string Shader::basic_frag_source =
    "#version 150 core\n"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
    "void main() {"
    "   outColor = texture( tex, Texcoord );"
    "}";