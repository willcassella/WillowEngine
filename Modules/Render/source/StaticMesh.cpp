// StaticMesh.cpp

#include <fstream>
#include <Utility\Array.h>
#include <Utility\Console.h>
#include "glew.h"
#include "..\include\Render\Vertex.h"
#include "..\include\Render\StaticMesh.h"
using namespace Willow;

bool LoadModel(const String& path, Array<Vertex>* const outVertices, Array<BufferID>* const outElements);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const String& path)
	: Super(path)
{
	Array<Vertex> vertices;
	Array<BufferID> elements;

	if (!LoadModel(path, &vertices, &elements))
	{
		return;
	}

	this->_numElements = elements.Size();

	// Generate buffers and upload data
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.Size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.Size() * sizeof(BufferID), &elements[0] , GL_STATIC_DRAW);

	glBindVertexArray(NULL);
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
	this->GetMaterial().Bind();

	// Upload the matrix to the GPU
	_mat->UploadModelMatrix(orientation);
	_mat->UploadViewMatrix(view);
	_mat->UploadProjectionMatrix(perspective);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)_numElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(NULL);
}

Material& StaticMesh::GetMaterial()
{
	return *_mat;
}

const Material& StaticMesh::GetMaterial() const
{
	return *_mat;
}

void StaticMesh::SetMaterial(const String& path)
{
	_mat = path;

	if (!_mat.IsLoaded())
	{
		return;
	}

	// Bind the VAO
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Set stuff
	BufferID vPosition;
	vPosition = glGetAttribLocation(_mat->GetID(), "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	BufferID vTexcoord = glGetAttribLocation(_mat->GetID(), "vTexcoord");
	glEnableVertexAttribArray(vTexcoord);
	glVertexAttribPointer(vTexcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vec3));

	BufferID vNormal = glGetAttribLocation(_mat->GetID(), "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(Vec3) + sizeof(Vec2)));

	glBindVertexArray(NULL);
}

bool LoadModel(const String& path, Array<Vertex>* const outVertices, Array<BufferID>* const outElements)
{
	// Attempt to open the file
	std::ifstream input;
	input.open(path.Cstr(), std::ios::binary | std::ios::in);

	// Make sure the file opened successfully
	if (!input.is_open())
	{
		Console::Warning("'@' could not be opened", path);
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

	Console::WriteLine("'@' loaded", path);

	return true;
}