// WillowConvert.h
#pragma once

#include <Utility\String.h>
#include <Utility\Array.h>
#include <Render\StaticMesh.h>
#include <Render\Vertex.h>

namespace Willow
{
	/** Enum of supported input types */
	enum class InputType
	{
		None, OBJ
	};

	// @TODO: Make these all normal functions, not part of a class (maybe a namespace instead)
	namespace WillowConvert
	{
		/////////////////////
		///   Functions   ///

		/** Converts a third-party file type (deduced by extension) into a Willow Engine file type */
		bool Convert(const String& path, const List<String>& options);

		///////////////////////////
		///   Parse Functions   ///

		/** Parses a file path, returning the file type */
		InputType ParsePath(const String& path);

		/** Parses a .obj file and fills an array of vertices and elements. 
		* Compression - whether to reduce the size of the mesh .dat file by reusing vertices where possible. May take a long time to parse. */
		bool ParseOBJFile(const String& path, Array<Vertex>* const outVertices, Array<BufferID>* const outElements, uint32 compression = 0);

		///////////////////////////
		///   Write Functions   ///

		/** Writes a mesh (defined by an array of vertices and elements) to a file that can be loaded by the engine */
		bool WriteStaticMesh(const String& name, const Array<Vertex>& vertices, const Array<BufferID>& elements);
	};
}