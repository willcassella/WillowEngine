// Material.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Containers/Union.h>
#include <Core/Math/Vec4.h>
#include <Resource/ResourceManager.h>
#include "Texture.h"
#include "Shader.h"

namespace willow
{
	struct ENGINE_API Material final
	{
		///////////////////////
		///   Inner Types   ///
	public:

		/** A material parameter may either be a float, Vec2, Vec3, Vec4, or texture. */
		using Param = Union<float, Vec2, Vec3, Vec4, ResourceHandle<Texture>>;
		
		/** A table mapping parameter names to parameter values. */
		using ParamTable = Table<String, Param>;

		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		Material(const Path& path);

		//////////////////
		///   Fields   ///
	public:

		/** The vertex shader for this Material. */
		ResourceHandle<Shader> vertex_shader;

		/** The fragment shader for this Material. */
		ResourceHandle<Shader> fragment_shader;

		/** The default parameters for this material. */
		ParamTable default_params;
	};
}
