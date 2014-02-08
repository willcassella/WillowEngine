#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vec3.h"
#include "Vec2.h"

struct Vertex
{
	// Vertex attributes
	Vec3 position;
	Vec2 coordinates;
	Vec3 normal;

	// == operator
	bool operator==( const Vertex& comp )
	{
		// Check position
		if( position != comp.position )
			return false;
		// Check coordinates
		if( coordinates != comp.coordinates  )
			return false;
		// Check normal
		if( normal != comp.normal )
			return false;

		// They all must have checked out
		return true;
	}

	bool operator!=( const Vertex& comp )
	{
		// Check position
		if( position != comp.position )
			return true;
		// Check coordinates
		if( coordinates != comp.coordinates )
			return true;
		// Check normal
		if( normal != comp.normal )
			return true;

		// They must have all been equal
		return false;
	}
};

#endif