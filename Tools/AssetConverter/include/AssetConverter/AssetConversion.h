// AssetConversion.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Resources/StaticMesh.h>

namespace willow
{
	namespace asset_conversion
	{
		/** Enum of supported input types */
		enum class InputType
		{
			None, OBJ
		};

		/////////////////////
		///   Functions   ///

		/** Converts a third-party file type (deduced by extension) into a Willow Engine file type */
		bool convert(const Path& path, const Array<String>& options);

		///////////////////////////
		///   Parse Functions   ///

		/** Parses a file path, returning the file type */
		InputType parse_path(const Path& path);

		/** Parses a .obj file and fills an array of vertices and elements.
		* 'compress' - Whether to reduce the size of the produced .wmesh file by reusing vertices where possible. May take a long time to parse. */
		bool parse_obj_file(const Path& path, Array<StaticMesh::Vertex>& outVertices);

		///////////////////////////
		///   Write Functions   ///

		/** Writes a mesh (defined by an array of vertices and elements) to a file that can be loaded by the engine */
		bool write_static_mesh(const Path& path, const Array<StaticMesh::Vertex>& vertices);
	}
}