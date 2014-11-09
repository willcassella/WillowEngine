// WillowConvert.h
#pragma once

#include <Utility\String.h>
#include <Utility\Array.h>
#include <Render\StaticMesh.h>
#include <Render\Vertex.h>

namespace Willow
{
	// @TODO: Make these all normal functions, not part of a class (maybe a namespace instead)
	namespace WillowConvert
	{
		/** Enum of supported input types */
		enum class InputType
		{
			None, OBJ
		};

		/////////////////////
		///   Functions   ///

		/** Converts a third-party file type (deduced by extension) into a Willow Engine file type */
		bool Convert(const String& path, const List<String>& options);

		///////////////////////////
		///   Parse Functions   ///

		/** Parses a file path, returning the file type */
		InputType ParsePath(const String& path);

		/** Parses a .obj file and fills an array of vertices and elements. 
		* compress - whether to reduce the size of the mesh .dat file by reusing vertices where possible. May take a long time to parse. */
		bool ParseOBJFile(const String& path, Array<Vertex>& outVertices, Array<uint32>& outElements, bool compress = false);

		///////////////////////////
		///   Write Functions   ///

		/** Writes a mesh (defined by an array of vertices and elements) to a file that can be loaded by the engine */
		bool WriteStaticMesh(const String& name, const Array<Vertex>& vertices, const Array<uint32>& elements);
	};
}