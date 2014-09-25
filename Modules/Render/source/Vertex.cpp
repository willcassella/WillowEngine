// Vertex.cpp

#include "..\include\Render\Vertex.h"
using namespace Willow;

/////////////////////
///   Operators   ///

bool Willow::operator==(const Vertex& lhs, const Vertex& rhs)
{
	if (lhs.Position != rhs.Position)
	{
		return false;
	}
	if (lhs.TextureCoordinates != rhs.TextureCoordinates)
	{
		return false;
	}
	if (lhs.Normal != rhs.Normal)
	{
		return false;
	}

	return true;
}

bool Willow::operator!=(const Vertex& lhs, const Vertex& rhs)
{
	if (lhs.Position != rhs.Position)
	{
		return true;
	}
	if (lhs.TextureCoordinates != rhs.TextureCoordinates)
	{
		return true;
	}
	if (lhs.Normal != rhs.Normal)
	{
		return true;
	}

	return false;
}