// StaticMesh.cpp

#include <fstream>
#include <iostream>
#include "glew.h"
#include "..\include\Render\Vertex.h"
#include "..\include\Render\StaticMesh.h"
using namespace Willow;

bool LoadBinaryModel(const String& path, Array<Vertex>* outVertices, Array<BufferID>* outElements);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const String& path)
	: Super(path)
{
	if (!LoadBinaryModel(path, &this->_vertices, &this->_elements))
	{
		this->_mat = nullptr;
		return;
	}

	// Generate buffers and upload data
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);
	
	glGenBuffers(1, &this->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	glBufferData(GL_ARRAY_BUFFER, this->_vertices.Size() * sizeof(Vertex), &this->_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_elements.Size() * sizeof(GLuint), &this->_elements[0] , GL_STATIC_DRAW);

	this->_mat = nullptr;

	glBindVertexArray(0);
}

StaticMesh::~StaticMesh()
{
	glDeleteBuffers(1, &this->_vbo);
	glDeleteBuffers(1, &this->_ebo);
	glDeleteVertexArrays(1, &this->_vao);
}

///////////////////
///   Methods   ///

void StaticMesh::Render(const Mat4& orientation, const Mat4& view, const Mat4& perspective) const
{
	// Bind the mesh
	glBindVertexArray(_vao);

	// Bind the material
	glUseProgram(this->GetMaterial());

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, this->GetMaterial().Textures->GetID());

	// Upload the matrix to the GPU
	glUniformMatrix4fv(this->GetMaterial().GetModelID(), 1, GL_FALSE, orientation[0]);
	glUniformMatrix4fv(this->GetMaterial().GetViewID(), 1, GL_FALSE, view[0]);
	glUniformMatrix4fv(this->GetMaterial().GetProjectionID(), 1, GL_FALSE, perspective[0]);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)this->GetNumElements(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

size_t StaticMesh::GetNumElements() const
{
	return this->_elements.Size();
}

Material& StaticMesh::GetMaterial() const
{
	return *this->_mat;
}

void StaticMesh::SetMaterial(Material& mat)
{
	_mat = &mat;

	// Bind the VAO
	glBindVertexArray(this->_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	// Set stuff
	BufferID vPosition;
	vPosition = glGetAttribLocation(*_mat, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	BufferID vTexcoord = glGetAttribLocation(*_mat, "vTexcoord");
	glEnableVertexAttribArray(vTexcoord);
	glVertexAttribPointer(vTexcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vec3));

	BufferID vNormal = glGetAttribLocation(*_mat, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(Vec3) + sizeof(Vec2)));

	glBindVertexArray(0);
}

bool LoadBinaryModel(const String& path, Array<Vertex>* outVertices, Array<BufferID>* outElements)
{
	// Attempt to open the file
	std::ifstream input;
	input.open(path.Cstr(), std::ios::binary | std::ios::in);

	// Make sure the file opened successfully
	if (!input.is_open())
	{
		std::cout << "WARNING: '" << path << "' could not be opened\n";
		return false;
	}

	// Get the number of vertices
	int num_verts;
	input.read((char*)&num_verts, sizeof(int32));

	// Add all the vertices
	for (int32 i = 0; i < num_verts; i++)
	{
		Vertex newVert;
		input.read((char*)&newVert, sizeof(Vertex));
		outVertices->Add(newVert);
	}

	// Get the number of elements
	int num_elems;
	input.read((char*)&num_elems, sizeof(int32));

	// Add all the elements
	for (int i = 0; i < num_elems; i++)
	{
		BufferID newElem;
		input.read((char*)&newElem, sizeof(uint32));
		outElements->Add(newElem);
	}

	// Close the file
	input.close();

	std::cout << "'" << path << "' loaded\n";

	return true;
}