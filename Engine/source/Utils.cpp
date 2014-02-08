// Util.cpp

#include <vector>
#include <fstream>
#include <cstdio>

#include <GL\glew.h>

#include "Utils.h"
#include "Vertex.h"
#include "Vec2.h"
#include "Vec3.h"

bool loadBinaryModel( const char * path,
    std::vector < Vertex > & out_vertices,
	std::vector < GLuint > & out_elements )
{
	// Attempt to open the file
	std::ifstream input;
	input.open( path, std::ios::binary | std::ios::in );

	// Make sure the file opened sucessfully
	if( !input.is_open() ) {
		std::printf( path );
		std::printf( " could not be opened!\n" );
		return false;
	}

	// Get the number of vertices
	int num_verts;
	input.read( (char*)&num_verts, sizeof( int ) );
	
	// Add all the vertices
	for( int i = 0; i < num_verts; i++ ) {
		Vertex newVert;
		input.read( (char*)&newVert, sizeof( Vertex ) );
		out_vertices.push_back( newVert );
	}

	// Get the number of elements
	int num_elems;
	input.read( (char*)&num_elems, sizeof( int ) );

	// Add all the elements
	for( int i = 0; i < num_elems; i++ ) {
		GLuint newElem;
		input.read( (char*)&newElem, sizeof( unsigned int ) );
		out_elements.push_back( newElem );
	}

	// Close the file
	input.close();

	return true;
}