// Shader.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Resource/Resources/TextFile.h>
#include "../../include/Engine/Assets/Shader.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Shader);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	Shader::Shader(const Path& path)
		: Base(path)
	{
		_source = TextFile(path).DumpLines();
	}
}
