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
    "#version 330 core\n"
    "in vec3 vPosition;"
	"in vec3 vNormal;"
    "in vec2 vTexcoord;"
	"out vec3 Position;"
	"out vec3 Normal;"
	"out vec2 Texcoord;"
	"uniform mat4 vModel;"
	"uniform mat4 vView;"
	"uniform mat4 vProjection;"
	"uniform float Time;"
    "void main() {"
	"   gl_Position = vProjection * vView * vModel * vec4( vPosition, 1.0 );"
	"	Texcoord = vec2( vTexcoord.x, 1.0 - vTexcoord.y );"
	"	Position = vPosition;"
	"	Normal = vNormal;"
    "}";

std::string Shader::basic_frag_source =
    "#version 330 core\n"
	"in vec3 Position;"
	"in vec3 Normal;"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
	"float depth = gl_FragDepth;"
    "void main() {"
	"   outColor = texture( tex, Texcoord );"
    "}";