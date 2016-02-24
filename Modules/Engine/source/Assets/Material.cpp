// Material.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/Assets/Material.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Material);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	Material::Material(const Path& path)
		: Base(path)
	{
		VertexShader = "Content/Shaders/default.vert"_p;
		FragmentShader = "Content/Shaders/default.frag"_p;
	}
}
