/*
This program converts text files to .DAT for faster loading by the engine
*/

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

#include "Vertex.h"
#include "Vec2.h"
#include "Vec3.h"

using namespace std;

// Enum of supported file types
enum FileType {
	NONE, OBJ
};

FileType parseFileName( 
	const string& fileName, 
	string& name, 
	string& extension );

bool parseOBJ(
    const char* path,
    vector< Vertex >& out_vertices,
	vector< unsigned int >& out_elements );

int main()
{
	// Prompt the user for a file to convert
	cout << "\n---WillowConvert version 0.6---\n\n";
	cout << "Enter the path to a file to convert:\n\n";
	cout << "  > ";

	// Get the user's filename
	string fileName;
	getline( cin, fileName );

	cout << endl;

	// Parse it
	string name, extension;
	FileType type = parseFileName( fileName, name, extension );

	// Check the returned type was valid
	if( type == NONE ) {
		// Must have been invalid
		cin.get();
		return 0;
	}

	// Attempt to open it
	vector< Vertex > vertices;
	vector< unsigned int > elements;
	if( !parseOBJ( fileName.c_str(), vertices, elements ) ) {
		// Opening failed
		cout << "Opening file failed!";
		return 0;
	}
	// Find the number of vertices
	int num_verts = (int)vertices.size();
	int num_elems = (int)elements.size();

	// Write it to a file
	ofstream output;
	output.open( (name + ".dat").c_str(), ios::binary | ios::out );

	output.write( (char*)&num_verts,	sizeof( int ) );
	output.write( (char*)&vertices[0],	sizeof( Vertex ) * num_verts );
	output.write( (char*)&num_elems,	sizeof( int ) );
	output.write( (char*)&elements[0],	sizeof( unsigned int ) * num_elems );

	output.close();
	
	cout << "All done!";
	cin.get();

	return 0;
}

FileType parseFileName( const string& fileName, string& name, string& extension )
{
	// Determine file name and extension
	for( int i = (int)fileName.length() - 1; i > 0; i-- ) {
		
		// Find the period
		if( fileName[i] == '.' ) {
			
			// Get the filename
			for( int j = 0; j < i; j++ ) {
				name += fileName[j];
			}

			// Get the extension
			for( int j = i + 1; j < fileName.length(); j++ ) {
				extension += fileName[j];
			}

			break;
		}
	}

	// Make sure the filename is valid
	if( extension.length() == 0 ) {
		// There was no extension
		cout << "Invalid filename: no extension" << endl;
		return NONE;
	}

	// Make the exension lower case
	transform( extension.begin(), extension.end(), extension.begin(), ::tolower );

	// Figure out what type of file it is.
	if( extension == "obj" ) {
		return OBJ;
	} else {
		// Filetype unknown
		cout << "Invalid filename: unknown type" << endl;
		return NONE;
	}
}

bool parseOBJ(
    const char* path,
    std::vector < Vertex > & out_vertices,
	std::vector < unsigned int > & out_elements
)
{
	std::vector < Vec3 > temp_positions;
	std::vector < Vec2 > temp_coordinates;
	std::vector < Vec3 > temp_normals;
	std::vector < Vertex > temp_vertices;
	
	FILE * file = fopen(path, "r");
	if( file == NULL )
	{
		printf("Impossible to open the file !\n");
		fclose( file );
		return false;
	}

	while( 1 )
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
 
		// Parse vertices
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			Vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_positions.push_back(vertex);
		}

		// Parse texture coordinates
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			Vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_coordinates.push_back(uv);
		}
		
		// Parse vertex normals
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			Vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		
		// Parse faces
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], 
				&normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9)
			{
				printf("File can't be read by OBJ parser : ( Try exporting with other options\n");
				fclose( file );
				return false;
			}

			// For each vertex in the face (3)
			for( int i = 0; i < 3; i++ )
			{
				// Construct a vertex
				Vertex vert;
				vert.position = temp_positions.at( vertexIndex[i] - 1 );
				vert.coordinates = temp_coordinates.at( uvIndex[i] - 1 );
				vert.normal = temp_normals.at( normalIndex[i] - 1 );

				// Search for the vertex
				bool search_failed = true;
				int index;
				for( index = 0; index < out_vertices.size(); index++ )
				{
					// if it already exists
					if( out_vertices[ index ] == vert )
					{
						// Add it to elements
						out_elements.push_back( index );
						search_failed = false;
						break;
					}
				}

				// If the vertex wash not found
				if( search_failed )
				{
					// Add the vertex to output
					out_vertices.push_back( vert );
					// Add it to elements
					out_elements.push_back( index );
				}
			}
		}
	}

	fclose( file );
	return true;
}