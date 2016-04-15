// Shader.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Resource/Resources/TextData.h>
#include "../../include/Engine/Resources/Shader.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Shader);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Shader::Shader(const Path& path)
	{
		const auto extension = path.get_file_extension();
		if (extension == "vert")
		{
			this->_type = Type::Vertex_Shader;
		}
		else if (extension == "frag")
		{
			this->_type = Type::Fragment_Shader;
		}
		else if (extension == "geom")
		{
			this->_type = Type::Geometry_Shader;
		}
		else
		{
			assert(false /* Unknown shader type! Extension must be one of: .vert .frag .geom*/);
		}

		this->_source = TextData{ path }.dump_lines();
	}
}
