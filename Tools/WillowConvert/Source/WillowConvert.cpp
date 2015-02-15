// WillowConvert.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include <Core/Console.h>
#include <Resource/TextFile.h>
#include <Resource/ResourceHandle.h>
#include "../include/WillowConvert/WillowConvert.h"

////////////////////////////
///   Public Functions   ///

bool WillowConvert::Convert(const String& path, const List<String>& options)
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

WillowConvert::InputType WillowConvert::ParsePath(const String& path)
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

bool WillowConvert::ParseOBJFile(const String& path, Array<Mesh::Vertex>& outVertices, Array<uint32>& outElements, bool compress)
{
	typedef Tuple<float, float, float> Position;
	typedef Pair<float, float> UVCoordinate;
	typedef Tuple<float, float, float> Normal;

	Array<Position> positions;
	Array<UVCoordinate> coordinates;
	Array<Normal> normals;

	ResourceHandle<TextFile> file(path);

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
			String::Parse(line, "v @ @ @", position.First, position.Second, position.Third);
			positions.Add(position);
			continue;
		}

		// Parse texture coordinates
		if (line.StartsWith("vt "))
		{
			UVCoordinate coordinate;
			String::Parse(line, "vt @ @", coordinate.First, coordinate.Second);
			coordinates.Add(coordinate);
			continue;
		}

		// Parse vertex normals
		if (line.StartsWith("vn "))
		{
			Normal normal;
			String::Parse(line, "vn @ @ @", normal.First, normal.Second, normal.Third);
			normals.Add(normal);
			continue;
		}

		// Parse faces
		if (line.StartsWith("f "))
		{
			uint32 vertexIndex[3], uvIndex[3], normalIndex[3];
			String::Parse(line, "f @/@/@ @/@/@ @/@/@", vertexIndex[0], uvIndex[0], normalIndex[0], vertexIndex[1], uvIndex[1], normalIndex[1], 
				vertexIndex[2], uvIndex[2], normalIndex[2]);

			// For each vertex in the face (3)
			for (uint32 i = 0; i < 3; ++i)
			{
				// Construct a vertex
				Mesh::Vertex vertex;
				Position position = positions[vertexIndex[i] - 1];
				vertex.X = position.First;
				vertex.Y = position.Second;
				vertex.Z = position.Third;

				UVCoordinate textureCoords = coordinates[uvIndex[i] - 1];
				vertex.U = textureCoords.First;
				vertex.V = textureCoords.Second;

				Normal normal = normals[normalIndex[i] - 1];
				vertex.I = normal.First;
				vertex.J = normal.Second;
				vertex.K = normal.Third;

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

bool WillowConvert::WriteStaticMesh(const String& name, const Array<Mesh::Vertex>& vertices, const Array<uint32>& elements)
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