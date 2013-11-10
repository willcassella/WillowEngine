#include "Utils.h"
#include "Vertex.h"
#include <GL\glew.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

bool loadOBJ(
    const char * path,
    std::vector < Vertex > & out_vertices,
	std::vector < GLuint > & out_elements
)
{
	std::vector < glm::vec3 > temp_positions;
	std::vector < glm::vec2 > temp_coordinates;
	std::vector < glm::vec3 > temp_normals;

	std::vector < Vertex	> temp_vertices;
	
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
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_positions.push_back(vertex);
		}

		// Parse texture coordinates
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_coordinates.push_back(uv);
		}
		
		// Parse vertex normals
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		
		// Parse faces
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
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