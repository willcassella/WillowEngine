// Material.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/Resources/Material.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Material);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Material::Material(const Path& /*path*/)
	{
		this->vertex_shader = "EngineContent/shaders/default.vert"_p;
		this->fragment_shader = "EngineContent/shaders/default.frag"_p;
	}
}
