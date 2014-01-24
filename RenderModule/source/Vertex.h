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
	bool operator==( Vertex comp )
	{
		// Check position
		if( position.x != comp.position.x || position.y != comp.position.y || position.z != comp.position.z )
			return false;
		// Check coordinates
		if( coordinates.x != comp.coordinates.x || coordinates.y != comp.coordinates.y )
			return false;
		// Check normal
		if( normal.x != comp.normal.x || normal.y != comp.normal.y || normal.z != comp.normal.z )
			return false;

		// They all must have checked out
		return true;
	}

	bool operator!=( Vertex comp )
	{
		// Check position
		if( position.x != comp.position.x || position.y != comp.position.y || position.z != comp.position.z )
			return true;
		// Check coordinates
		if( coordinates.x != comp.coordinates.x || coordinates.y != comp.coordinates.y )
			return true;
		// Check normal
		if( normal.x != comp.normal.x || normal.y != comp.normal.y || normal.z != comp.normal.z )
			return true;

		// They must have all been equal
		return false;
	}
};

#endif