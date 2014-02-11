#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vec3.h"
#include "Vec2.h"

struct Vertex
{
	////////////////
	///   Data   ///
	////////////////
public:

	Vec3 position;
	Vec2 coordinates;
	Vec3 normal;

	//////////////////////////////
	///   Operator Overloads   ///
	//////////////////////////////

	// Returns TRUE if this vertex is equivilent to another vertex
	bool operator==( const Vertex& rhs )
	{
		// Check position
		if( position != rhs.position )
			return false;
		// Check coordinates
		if( coordinates != rhs.coordinates  )
			return false;
		// Check normal
		if( normal != rhs.normal )
			return false;

		// They all must have checked out
		return true;
	}

	// Returns TRUE if this vertex is NOT equivilent to another vertex
	bool operator!=( const Vertex& rhs )
	{
		// Check position
		if( position != rhs.position )
			return true;
		// Check coordinates
		if( coordinates != rhs.coordinates )
			return true;
		// Check normal
		if( normal != rhs.normal )
			return true;

		// They must have all been equal
		return false;
	}
};

#endif