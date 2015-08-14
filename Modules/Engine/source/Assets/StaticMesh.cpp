// Mesh.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Console.h>
#include "../../include/Engine/Assets/StaticMesh.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(StaticMesh);

////////////////////////
///   Constructors   ///

StaticMesh::StaticMesh(const Path& path)
	: Base(path)
{
	BinaryFile file(path);
	const byte* cursor = file.GetData();

	// Get the number of vertices
	uint32 numVerts = *reinterpret_cast<const uint32*>(cursor);

	cursor += sizeof(uint32);

	// Load in vertices
	Vertices = Array<Vertex>(reinterpret_cast<const Vertex*>(cursor), numVerts);

	cursor += sizeof(Vertex) * numVerts;

	// Get the number of elements
	uint32 numElems = *reinterpret_cast<const uint32*>(cursor);

	cursor += sizeof(uint32);

	// Load in elements
	Elements = Array<uint32>(reinterpret_cast<const uint32*>(cursor), numElems);
}
