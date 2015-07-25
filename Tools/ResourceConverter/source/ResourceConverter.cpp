// ResourceConverter.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Console.h>
#include <Core/Resource/ResourcePtr.h>
#include <Common/TextFile.h>
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
	struct Position { float X; float Y; float Z; };
	struct UVCoordinate { float U; float V; };
	struct Normal { float I; float J; float K; };

	Array<Position> positions;
	Array<UVCoordinate> coordinates;
	Array<Normal> normals;

	ResourcePtr<TextFile> file(path);

	if (!file.IsLoaded())
	{
		return false;
	}

	for (const String& line : file->GetLines())
	{
		// Parse vertices
		if (line.StartsWith("v "))
		{
			Position position;
			FromString(line, "v @ @ @", position.X, position.Y, position.Z);
			positions.Add(position);
			continue;
		}

		// Parse texture coordinates
		if (line.StartsWith("vt "))
		{
			UVCoordinate coordinate;
			FromString(line, "vt @ @", coordinate.U, coordinate.V);
			coordinates.Add(coordinate);
			continue;
		}

		// Parse vertex normals
		if (line.StartsWith("vn "))
		{
			Normal normal;
			FromString(line, "vn @ @ @", normal.I, normal.J, normal.K);
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
				Position position = positions[vertexIndex[i] - 1];
				vertex.X = position.X;
				vertex.Y = position.Y;
				vertex.Z = position.Z;

				UVCoordinate textureCoords = coordinates[uvIndex[i] - 1];
				vertex.U = textureCoords.U;
				vertex.V = textureCoords.V;

				Normal normal = normals[normalIndex[i] - 1];
				vertex.I = normal.I;
				vertex.J = normal.J;
				vertex.K = normal.K;

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
	std::ofstream output;
	output.open((name + ".wmesh").Cstr(), std::ios::binary | std::ios::out);

	output.write((char*)&numVerts, sizeof(uint32));
	output.write((char*)&vertices[0], sizeof(Mesh::Vertex) * numVerts);
	output.write((char*)&numElements, sizeof(uint32));
	output.write((char*)&elements[0], sizeof(uint32) * numElements);

	output.close();

	return true;
}