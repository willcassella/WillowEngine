#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Shader.h"
#include "Texture.h"

//TODO: make this more than just a shader program
class Material
{
public:

	Material();
	Material( Shader *_vertex, Shader *_fragment ); //TODO: add texture support
	~Material();

	// Load and unload material information to GPU
	void Load( Shader *_vertex, Shader *_fragment );
	void Unload();

	GLuint id;
	Texture *texture;

	GLuint clipspace;

private:

	// Holds whether material has been loaded to GPU
	bool loaded;

	// Material information
	Shader *vertex;
	Shader *fragment;
};

#endif