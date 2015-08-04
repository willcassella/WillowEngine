// ResourceConverter.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Console.h>
#include <Resource/TextFile.h>
#include "../include/ResourceConverter/ResourceConverter.h"

////////////////////////////
///   Public Functions   ///

bool ResourceConverter::Convert(const String& path, const Array<String>& options)
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
		Array<Mesh::Vertex> vertices;
		Array<uint32> elements;

		if (!ParseOBJFile(path, vertices, elements, 0))
		{
			return false;
		}
		if (!WriteStaticMesh(String::GetFileName(path), vertices, elements))
		{
			return false;
		}
		return true;
	}

	Console::WriteLine("Conversion finished");

	return true;
}

///////////////////////////
///   Parse Functions   ///

ResourceConverter::InputType ResourceConverter::ParsePath(const String& path)
{
	String extension = String::GetFileExtension(path);

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

bool ResourceConverter::ParseOBJFile(const String& path, Array<Mesh::Vertex>& outVertices, Array<uint32>& outElements, bool compress)
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
			FromString(line, "v @ @ @", position.X, position.Y, position.Z);
			positions.Add(position);
			continue;
		}

		// Parse texture coordinates
		if (line.StartsWith("vt "))
		{
			Vec2 coordinate;
			FromString(line, "vt @ @", coordinate.X, coordinate.Y);
			coordinates.Add(coordinate);
			continue;
		}

		// Parse vertex normals
		if (line.StartsWith("vn "))
		{
			Vec3 normal;
			FromString(line, "vn @ @ @", normal.X, normal.Y, normal.Z);
			normals.Add(normal);
			continue;
		}

		// Parse faces
		if (line.StartsWith("f "))
		{
			uint32 vertexIndex[3], uvIndex[3], normalIndex[3];
			FromString(line, "f @/@/@ @/@/@ @/@/@", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1], 
				vertexIndex[2], uvIndex[2], normalIndex[2]);

			// For each vertex in the face (3)
			for (uint32 i = 0; i < 3; ++i)
			{
				// Construct a vertex
				Mesh::Vertex vertex;
				Vec3 position = positions[vertexIndex[i] - 1];
				vertex.Position = position;

				Vec2 textureCoords = coordinates[uvIndex[i] - 1];
				vertex.UV = textureCoords;

				Vec3 normal = normals[normalIndex[i] - 1];
				vertex.Normal = normal;

				if (compress)
				{
					// Search for the vertex
					bool duplicateFound = false;
					uint32 index = 0;
					for (const auto& vert : outVertices)
					{
						// if it already exists
						if (vert == vertex)
						{
							// Add its index to elements
							outElements.Add(index);
							duplicateFound = true;
							break;
						}
						index++;
					}

					if (!duplicateFound)
					{
						outVertices.Add(vertex);
						outElements.Add(index);
					}
				}
				else
				{
					outVertices.Add(vertex);
					outElements.Add(outVertices.Size() - 1);
				}
			}
		}
	}

	return true;
}

///////////////////////////
///   Write Functions   ///

bool ResourceConverter::WriteStaticMesh(const String& name, const Array<Mesh::Vertex>& vertices, const Array<uint32>& elements)
{
	// Get the size of each array
	uint32 numVerts = vertices.Size();
	uint32 numElements = elements.Size();

	// Write it to a file
	std::basic_fstream<byte> output;
	output.open((name + ".wmesh").Cstr(), std::ios::binary | std::ios::out);

	output.write((byte*)&numVerts, sizeof(uint32));
	output.write((byte*)&vertices[0], sizeof(Mesh::Vertex) * numVerts);
	output.write((byte*)&numElements, sizeof(uint32));
	output.write((byte*)&elements[0], sizeof(uint32) * numElements);

	output.close();

	return true;
}