// StaticMesh.cpp

#include <fstream>
#include <Utility\Array.h>
#include <Utility\Console.h>
#include "glew.h"
#include "..\include\Render\Vertex.h"
#include "..\include\Render\StaticMesh.h"
using namespace Willow;

bool LoadModel(const String& path, Array<Vertex>& outVertices, Array<uint32>& outElements);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const String& path)
	: Super(path)
{
	Array<Vertex> vertices;
	Array<uint32> elements;

	if (!LoadModel(path, vertices, elements))
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.Size() * sizeof(uint32), &elements[0] , GL_STATIC_DRAW);

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
	this->GetMaterial()->Bind();

	// Upload the matrix to the GPU
	_mat->UploadModelMatrix(orientation);
	_mat->UploadViewMatrix(view);
	_mat->UploadProjectionMatrix(perspective);

	//Draw the mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)_numElements, GL_UNSIGNED_INT, 0);

	glBindVertexArray(NULL);
}

ResourcePtr<Material>& StaticMesh::GetMaterial()
{
	return _mat;
}

const ResourcePtr<Material>& StaticMesh::GetMaterial() const
{
	return _mat;
}

void StaticMesh::SetMaterial(const ResourcePtr<Material>& material)
{
	_mat = material;

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
	glVertexAttribPointer(vTexcoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

	BufferID vNormal = glGetAttribLocation(_mat->GetID(), "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(float) * 3 + sizeof(float) * 2));

	glBindVertexArray(NULL);
}

bool LoadModel(const String& path, Array<Vertex>& outVertices, Array<uint32>& outElements)
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
	uint32 numVerts;
	input.read((char*)&numVerts, sizeof(uint32));
	outVertices.Reset(numVerts);

	// Add all the vertices
	for (uint32 i = 0; i < numVerts; ++i)
	{
		Vertex newVert;
		input.read((char*)&newVert, sizeof(Vertex));
		outVertices.Add(newVert);
	}

	// Get the number of elements
	uint32 numElems;
	input.read((char*)&numElems, sizeof(uint32));
	outElements.Reset(numElems);

	// Add all the elements
	for (uint32 i = 0; i < numElems; ++i)
	{
		uint32 newElem;
		input.read((char*)&newElem, sizeof(uint32));
		outElements.Add(newElem);
	}

	// Close the file
	input.close();

	Console::WriteLine("'@' loaded", path);

	return true;
}