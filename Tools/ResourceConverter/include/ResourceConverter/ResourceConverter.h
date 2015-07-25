// ResourceConverter.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Common/Mesh.h>

namespace ResourceConverter
{
	/** Enum of supported input types */
	enum class InputType
	{
		None, OBJ
	};

	/////////////////////
	///   Functions   ///

	/** Converts a third-party file type (deduced by extension) into a Willow Engine file type */
	bool Convert(const String& path, const Array<String>& options);

	///////////////////////////
	///   Parse Functions   ///

	/** Parses a file path, returning the file type */
	InputType ParsePath(const String& path);

	/** Parses a .obj file and fills an array of vertices and elements. 
	* 'compress' - Whether to reduce the size of the produced .wmesh file by reusing vertices where possible. May take a long time to parse. */
	bool ParseOBJFile(const String& path, Array<Mesh::Vertex>& outVertices, Array<uint32>& outElements, bool compress = false);

	///////////////////////////
	///   Write Functions   ///

	/** Writes a mesh (defined by an array of vertices and elements) to a file that can be loaded by the engine */
	bool WriteStaticMesh(const String& name, const Array<Mesh::Vertex>& vertices, const Array<uint32>& elements);
};