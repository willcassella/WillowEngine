#ifndef STATICMESH_H_
#define STATICMESH_H_

#include <string>
#include <vector>
#include "Material.h"
#include "Vertex.h"

typedef std::vector< Vertex > VertexArray;
typedef std::vector< GLuint > ElementArray;

class StaticMesh
{	
	////////////////
	///   Data   ///
	////////////////
private:

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	VertexArray vertices;
	ElementArray elements;

	Material* mat;

	////////////////////////
	///   Constructors   ///
	////////////////////////
public:

	StaticMesh( const std::string& path );
	~StaticMesh();

	///////////////////////////////
	///   Getters and Setters   ///
	///////////////////////////////
public:

	GLuint getVAO() const;
	std::size_t getNumElements() const;
	
	Material& getMaterial() const;
	void setMaterial( Material& _mat );
};

#endif