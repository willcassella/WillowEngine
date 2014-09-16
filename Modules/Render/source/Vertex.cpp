// Vertex.cpp

#include "..\include\Render\Vertex.h"
using namespace Willow;

/////////////////////
///   Operators   ///

bool Vertex::operator==(const Vertex& rhs)
{
	if (Position != rhs.Position)
	{
		return false;
	}
	if (TextureCoordinates != rhs.TextureCoordinates)
	{
		return false;
	}
	if (Normal != rhs.Normal)
	{
		return false;
	}

	return true;
}

bool Vertex::operator!=(const Vertex& rhs)
{
	if (Position != rhs.Position)
	{
		return true;
	}
	if (TextureCoordinates != rhs.TextureCoordinates)
	{
		return true;
	}
	if (Normal != rhs.Normal)
	{
		return true;
	}

	return false;
}