// Shader.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Path.h>
#include "../config.h"

namespace willow
{
	struct ENGINE_API Shader final
	{
		/////////////////
		///   Types   ///
	public:

		enum class Type : byte
		{
			Vertex_Shader,
			Fragment_Shader,
			Geometry_Shader
		};

		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		Shader(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the source code for this Shader. */
		FORCEINLINE const String& get_source() const
		{
			return this->_source;
		}

		/** Returns the type of shader this is. */
		FORCEINLINE Type get_shader_type() const
		{
			return this->_type;
		}

		////////////////
		///   Data   ///
	private:

		String _source;
		Type _type;
	};
}
