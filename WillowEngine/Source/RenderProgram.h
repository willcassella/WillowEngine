#ifndef RENDERPROGRAM_H_
#define RENDERPROGRAM_H_

#include "headers.h"
#include "Shader.h"

class RenderProgram
{
private:
	Shader FragShader;
	Shader VertShader;
	Shader GeoShader;
	GLint id;

public:
	RenderProgram();
	RenderProgram( Shader INIT_VertShader, Shader INIT_FragShader );
	RenderProgram( Shader INIT_VertShader, Shader INIT_FragShader, Shader INIT_GeoShader );
	~RenderProgram();
	operator GLint();

	void init();
	void compile();
	void addShader( Shader shader );
	void use();
	GLint getId();
};

#endif