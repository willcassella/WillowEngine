// Mesh.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Console.h>
#include "../include/Resource/Mesh.h"

/////////////////////
///   Functions   ///

// @TODO: Merge this with the constructor?
bool LoadModel(const String& path, Array<Mesh::Vertex>& outVertices, Array<uint32>& outElements)
{
	// Attempt to open the file
	std::ifstream file;
	file.open(path.Cstr(), std::ios::binary | std::ios::in);

	// Make sure the file opened successfully
	if (!file.is_open())
	{
		file.close();
		return false;
	}

	// Get the number of vertices
	uint32 numVerts;
	file.read((char*)&numVerts, sizeof(uint32));
	outVertices.Reset(numVerts);

	// Add all the vertices
	for (uint32 i = 0; i < numVerts; ++i)
	{
		Mesh::Vertex newVert;
		file.read((char*)&newVert, sizeof(Mesh::Vertex));
		outVertices.Add(newVert);
	}

	// Get the number of elements
	uint32 numElems;
	file.read((char*)&numElems, sizeof(uint32));
	outElements.Reset(numElems);

	// Add all the elements
	for (uint32 i = 0; i < numElems; ++i)
	{
		uint32 newElem;
		file.read((char*)&newElem, sizeof(uint32));
		outElements.Add(newElem);
	}

	file.close();
	return true;
}

////////////////////////
///   Mesh::Vertex   ///

bool operator==(const Mesh::Vertex& lhs, const Mesh::Vertex& rhs)
{
	// Compare position
	if (lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z)
	{
		return false;
	}
	// Compare texture coordinates
	if (lhs.U != rhs.Y || lhs.V != rhs.V)
	{
		return false;
	}
	// Compare normal direction
	if (lhs.I != rhs.I || lhs.J != rhs.J || lhs.K != rhs.K)
	{
		return false;
	}

	return true;
}

bool operator!=(const Mesh::Vertex& lhs, const Mesh::Vertex& rhs)
{
	return !(lhs == rhs);
}

////////////////
///   Mesh   ///

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Mesh);

////////////////////////
///   Constructors   ///

Mesh::Mesh(const String& path)
	: Super(path)
{
	if (!LoadModel(path, Vertices, Elements))
	{
		Console::Warning("'@' could not be opened", path);
		return;
	}

	Console::WriteLine("'@' loaded successfully", path);
}