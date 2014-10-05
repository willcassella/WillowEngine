// WillowConvert.cpp

#include <fstream>
#include <cstring>
#include <Utility\Console.h>
#include "..\include\WillowConvert\WillowConvert.h"
using namespace Willow;

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
		Array<Vertex> vertices;
		Array<BufferID> elements;

		if (!ParseOBJFile(path, &vertices, &elements, 0))
		{
			return false;
		}
		if (!WriteStaticMesh(path.GetFileName(), vertices, elements))
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
	String extension = path.GetFileExtension();

	// Make sure the filename is valid
	if (extension.IsNullOrEmpty())
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

bool WillowConvert::ParseOBJFile(const String& path, Array<Vertex>* const outVertices, Array<BufferID>* const outElements, uint32 compression)
{
	Array<Vec3> positions;
	Array<Vec2> coordinates;
	Array<Vec3> normals;

	FILE* file = fopen(path.Cstr(), "r");
	if (file == NULL)
	{
		Console::Error("'@' does not exist!", path);
		return false;
	}

	while (true)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		// Parse vertices
		if (strcmp(lineHeader, "v") == 0)
		{
			Vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.X, &vertex.Y, &vertex.Z);
			positions.Add(vertex);
			continue;
		}

		// Parse texture coordinates
		if (strcmp(lineHeader, "vt") == 0)
		{
			Vec2 coordinate;
			fscanf(file, "%f %f\n", &coordinate.X, &coordinate.Y);
			coordinates.Add(coordinate);
			continue;
		}

		// Parse vertex normals
		if (strcmp(lineHeader, "vn") == 0)
		{
			Vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.X, &normal.Y, &normal.Z);
			normals.Add(normal);
			continue;
		}

		// Parse faces
		if (strcmp(lineHeader, "f") == 0)
		{
			uint32 vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1],
				&normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				Console::Error("'@' can't be read by OBJ parser : Try exporting with other options", path);
				fclose(file);
				return false;
			}

			// For each vertex in the face (3)
			for (int32 i = 0; i < 3; i++)
			{
				// Construct a vertex
				Vertex vertex;
				vertex.Position = positions[vertexIndex[i] - 1];
				vertex.TextureCoordinates = coordinates[uvIndex[i] - 1];
				vertex.Normal = normals[normalIndex[i] - 1];

				if (compression > 0)
				{
					// Search for the vertex
					bool duplicateFound = false;
					BufferID index = 0;
					for (const auto& vert : *outVertices)
					{
						// if it already exists
						if (vert == vertex)
						{
							// Add its index to elements
							outElements->Add(index);
							duplicateFound = true;
							break;
						}
						index++;
					}

					if (!duplicateFound)
					{
						outVertices->Add(vertex);
						outElements->Add(index);
					}
				}
				else
				{
					outVertices->Add(vertex);
					outElements->Add(outVertices->Size() - 1);
				}
			}
		}
	}

	fclose(file);
	return true;
}

///////////////////////////
///   Write Functions   ///

bool WillowConvert::WriteStaticMesh(const String& name, const Array<Vertex>& vertices, const Array<BufferID>& elements)
{
	// Get the size of each array
	uint32 numVerts = vertices.Size();
	uint32 numElements = elements.Size();

	// Write it to a file
	std::ofstream output;
	output.open((name + ".dat").Cstr(), std::ios::binary | std::ios::out);

	output.write((char*)&numVerts, sizeof(uint32));
	output.write((char*)&vertices[0], sizeof(Vertex) * numVerts);
	output.write((char*)&numElements, sizeof(uint32));
	output.write((char*)&elements[0], sizeof(BufferID) * numElements);

	output.close();

	return true;
}