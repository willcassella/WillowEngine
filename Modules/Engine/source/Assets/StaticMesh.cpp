// Mesh.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Console.h>
#include "../../include/Engine/Assets/StaticMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(StaticMesh);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const BinaryFile& file)
	: Base(file)
{
	OnReload();
}

///////////////////
///   Methods   ///

void StaticMesh::OnReload()
{
	const byte* cursor = static_cast<const BinaryFile&>(GetResource()).GetData();

	// Get the number of vertices
	uint32 numVerts = *(const uint32*)cursor;

	cursor += sizeof(uint32);

	// Load in vertices
	Vertices = Array<Vertex>((const Vertex*)cursor, numVerts);

	cursor += sizeof(Vertex) * numVerts;

	// Get the number of elements
	uint32 numElems = *(uint32*)cursor;

	cursor += sizeof(uint32);

	// Load in elements
	Elements = Array<uint32>((const uint32*)cursor, numElems);
}
