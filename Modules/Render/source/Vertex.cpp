// Vertex.cpp

#include "..\include\Render\Vertex.h"
using namespace Willow;

/////////////////////
///   Operators   ///

bool Willow::operator==(const Vertex& lhs, const Vertex& rhs)
{
	// Compare position
	if (lhs.X != rhs.X || lhs.Y != rhs.Y || lhs.Z != rhs.Z)
	{
		return false;
	}
	// Compare texture coordinates
	if (lhs.U != rhs.Y || lhs.V != rhs.V)
	{
		return false;
	}
	// Compare normal direction
	if (lhs.I != rhs.I || lhs.J != rhs.J || lhs.K != rhs.K)
	{
		return false;
	}

	return true;
}