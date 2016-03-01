// AssetConversion.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/IO/Console.h>
#include <Resource/Resources/TextFile.h>
#include "../include/AssetConverter/AssetConversion.h"

namespace Willow
{
	namespace AssetConversion
	{
		/////////////////////
		///   Functions   ///

		bool Convert(const Path& path, const Array<String>& /*options*/)
		{
			InputType input = ParsePath(path);

			// If parsing failed
			if (input == InputType::None)
			{
				return true;
			}

			// If we're parsing an OBJ file
			if (input == InputType::OBJ)
			{
				Array<StaticMesh::Vertex> vertices;

				if (!ParseOBJFile(path, vertices))
				{
					return false;
				}
				if (!WriteStaticMesh(path.GetFileName(), vertices))
				{
					return false;
				}
				return true;
			}

			Console::WriteLine("Conversion finished");

			return true;
		}

		InputType ParsePath(const Path& path)
		{
			String extension = path.GetFileExtension();

			// Make sure the filename is valid
			if (extension.IsEmpty())
			{
				// There was no extension
				Console::Error("Invalid filename: no extension");
				return InputType::None;
			}

			// Make the extension lower case
			extension = extension.ToLower();

			// Figure out what type of file it is.
			if (extension == "obj")
			{
				return InputType::OBJ;
			}
			else
			{
				// File type unknown
				Console::Error("Invalid filename: unknown type");
				return InputType::None;
			}
		}

		bool ParseOBJFile(const Path& path, Array<StaticMesh::Vertex>& outVertices)
		{
			Array<Vec3> positions;
			Array<Vec2> coordinates;
			Array<Vec3> normals;

			TextFile file(path);

			for (const String& line : file.GetLines())
			{
				// Parse vertices
				if (line.StartsWith("v "))
				{
					Vec3 position;
					Parse(line, "v @ @ @", position.X, position.Y, position.Z);
					positions.Add(position);
					continue;
				}

				// Parse texture coordinates
				if (line.StartsWith("vt "))
				{
					Vec2 coordinate;
					Parse(line, "vt @ @", coordinate.X, coordinate.Y);
					coordinates.Add(coordinate);
					continue;
				}

				// Parse vertex normals
				if (line.StartsWith("vn "))
				{
					Vec3 normal;
					Parse(line, "vn @ @ @", normal.X, normal.Y, normal.Z);
					normals.Add(normal);
					continue;
				}

				// Parse faces
				if (line.StartsWith("f "))
				{
					uint32 vertexIndex[3], uvIndex[3], normalIndex[3];
					Parse(line, "f @/@/@ @/@/@ @/@/@", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1],
						vertexIndex[2], uvIndex[2], normalIndex[2]);

					// For each vertex in the face (3)
					for (uint32 i = 0; i < 3; ++i)
					{
						// Construct a vertex
						StaticMesh::Vertex vertex;
						Vec3 position = positions[vertexIndex[i] - 1];
						vertex.Position = position;

						Vec2 textureCoords = coordinates[uvIndex[i] - 1];
						vertex.UV = textureCoords;

						Vec3 normal = normals[normalIndex[i] - 1];
						vertex.Normal = normal;

						outVertices.Add(vertex);
					}
				}
			}

			return true;
		}

		bool WriteStaticMesh(const Path& name, const Array<StaticMesh::Vertex>& vertices)
		{
			// Get the size of each array
			uint32 numVerts = static_cast<uint32>(vertices.Size());

			// Write it to a file
			std::ofstream output;
			output.open((name + ".wmesh"_s).Cstr(), std::ios::binary | std::ios::out);

			output.write((char*)&numVerts, sizeof(uint32));
			output.write((char*)&vertices[0], sizeof(StaticMesh::Vertex) * numVerts);

			output.close();
			return true;
		}
	}
}