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
	GLuint vModel;
	GLuint vView;
	GLuint vProjection;
	GLuint Time;

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
	GLuint getModelID() const;
	GLuint getViewID() const;
	GLuint getProjectionID() const;
	GLuint getTimeID() const;
};

#endif