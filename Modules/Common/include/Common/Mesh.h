// Mesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Resource/Resource.h>
#include "config.h"

class COMMON_API Mesh : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Resource);

	///////////////////////
	///   Inner Types   ///
public:

	struct COMMON_API Vertex final
	{
		//////////////////
		///   Fields   ///
	public:

		float X, Y, Z;	// Position coordinates
		float U, V;		// UV coordinates
		float I, J, K;	// Normal direction

		/////////////////////
		///   Operators   ///
	public:

		friend COMMON_API bool operator==(const Vertex& lhs, const Vertex& rhs);
		friend COMMON_API bool operator!=(const Vertex& lhs, const Vertex& rhs);
	};

	////////////////////////
	///   Constructors   ///
public:

	Mesh(const String& path);

	//////////////////
	///   Fields   ///
public:

	Array<Vertex> Vertices;
	Array<uint32> Elements;
};
