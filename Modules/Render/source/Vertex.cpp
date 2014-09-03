// Vertex.cpp

#include "..\include\Render\Vertex.h"
using namespace Render;

/////////////////////
///   Operators   ///

bool Vertex::operator==(const Vertex& rhs)
{
	// Check position
	if (position != rhs.position)
	{
		return false;
	}
	// Check coordinates
	if (coordinates != rhs.coordinates)
	{
		return false;
	}
	// Check normal
	if (normal != rhs.normal)
	{
		return false;
	}

	// They all must have checked out
	return true;
}

bool Vertex::operator!=(const Vertex& rhs)
{
	// Check position
	if (position != rhs.position)
	{
		return true;
	}
	// Check coordinates
	if (coordinates != rhs.coordinates)
	{
		return true;
	}
	// Check normal
	if (normal != rhs.normal)
	{
		return true;
	}

	// They must have all been equal
	return false;
}