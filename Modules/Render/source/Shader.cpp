// Shader.cpp

#include "glew.h"
#include "..\include\Render\shader.h"
using namespace Render;


////////////////////////
///   Constructors   ///

Shader::Shader(const Willow::String& _source, ShaderType::ShaderType type)
{
	this->source = _source;
	const char* temp_source = source;

	switch (type)
	{
	case ShaderType::VERTEX_SHADER:
		this->id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::FRAGMENT_SHADER:
		this->id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::GEOMERTY_SHADER:
		this->id = glCreateShader(GL_GEOMETRY_SHADER);
	}

	glShaderSource(this->id, 1, &temp_source, nullptr);
	glCompileShader(this->id);
}

Shader::~Shader()
{
	glDeleteShader(this->id);
}

///////////////////////////////
///   Getters and Setters   ///

BufferID Shader::getID() const
{
	return this->id;
}

//////////////////////////
///   Static Members   ///

const Willow::String Shader::basic_vert_source =
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
    "void main() {"
	"   gl_Position = vProjection * vView * vModel * vec4(vPosition, 1.0);"
	"	Texcoord = vec2(vTexcoord.x, 1.0 - vTexcoord.y);"
	"	Position = vPosition;"
	"	Normal = vNormal;"
    "}";

const Willow::String Shader::basic_frag_source =
    "#version 330 core\n"
	"in vec3 Position;"
	"in vec3 Normal;"
    "in vec2 Texcoord;"
    "out vec4 outColor;"
    "uniform sampler2D tex;"
	"float depth = gl_FragDepth;"
    "void main() {"
	"   outColor = texture(tex, Texcoord);"
    "}";