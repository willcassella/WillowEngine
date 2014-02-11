#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Shader.h"
#include "Texture.h"

class Material
{
	////////////////
	///   Data   ///
	////////////////
private:

	GLuint id;
	GLuint clipspace;

	Texture* texture;
	Shader* vertex;
	Shader* fragment;

	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	Material( const Shader& _vertex, const Shader& _fragment );
	~Material();

	///////////////////////////////
	///   Getters and Setters   ///
	///////////////////////////////
public:

	GLuint getID() const;
	Texture& getTexture() const;
	void setTexture( const Texture& _TEX );
	GLuint getClipSpaceID() const;
};

#endif