#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Shader.h"

//TODO: make this not a render program
class Material
{
public:
	Material( Shader *_vertex, Shader *_fragment ); //TODO: add texture support
	~Material();

	Shader *vertex;
	Shader *fragment;

	GLuint vao;
	GLuint id;

	//static Material basic;
};

#endif