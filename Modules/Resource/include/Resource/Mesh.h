// Mesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "SystemResource.h"

class RESOURCE_API Mesh : public SystemResource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(SystemResource);

	///////////////////////
	///   Inner Types   ///
public:

	struct RESOURCE_API Vertex final
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

		friend RESOURCE_API bool operator==(const Vertex& lhs, const Vertex& rhs);
		friend RESOURCE_API bool operator!=(const Vertex& lhs, const Vertex& rhs);
	};

	////////////////////////
	///   Constructors   ///
public:

	Mesh(const String& path);
	Mesh(const Mesh& copy) = delete;
	Mesh(Mesh&& other) = delete;

	//////////////////
	///   Fields   ///
public:

	Array<Vertex> Vertices;
	Array<uint32> Elements;

	/////////////////////
	///   Operators   ///
public:

	Mesh& operator=(const Mesh& copy) = delete;
	Mesh& operator=(Mesh&& other) = delete;
};