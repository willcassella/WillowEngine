#ifndef STATICMESH_H_
#define STATICMESH_H_

#include <string>
#include <vector>
#include "object.h"
#include "Material.h"
#include "Vertex.h"

typedef std::vector< Vertex > VertexArray;
typedef std::vector< GLuint > ElementArray;

class StaticMesh : public object
{	
	REGISTER(StaticMesh);

	////////////////////////
	///   Constructors   ///

	StaticMesh(const std::string& path);
	~StaticMesh();

	////////////////
	///   Data   ///
private:

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	VertexArray vertices;
	ElementArray elements;

	Material* mat;

	///////////////////////////////
	///   Getters and Setters   ///
public:

	GLuint getVAO() const;
	std::size_t getNumElements() const;
	
	Material& getMaterial() const;
	void setMaterial( Material& _mat );
};

#endif