// StaticMesh.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Resource/Asset.h>
#include "../config.h"

class ENGINE_API StaticMesh final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Asset)

	///////////////////////
	///   Inner Types   ///
public:

	struct ENGINE_API Vertex final
	{
		//////////////////
		///   Fields   ///
	public:

		Vec3 Position;	// Position coordinates
		Vec2 UV;		// UV coordinates
		Vec3 Normal;	// Normal direction

		/////////////////////
		///   Operators   ///
	public:

		friend FORCEINLINE bool operator==(const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.Position == rhs.Position && lhs.UV == rhs.UV && lhs.Normal == rhs.Normal;
		}
		friend FORCEINLINE bool operator!=(const Vertex& lhs, const Vertex& rhs)
		{
			return !(lhs == rhs);
		}
	};

	////////////////////////
	///   Constructors   ///
public:

	StaticMesh(const Path& path);

	//////////////////
	///   Fields   ///
public:

	Array<Vertex> Vertices;
	Array<uint32> Elements;
};
