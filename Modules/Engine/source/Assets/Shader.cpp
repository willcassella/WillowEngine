// Shader.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Resource/Resources/TextFile.h>
#include "../../include/Engine/Assets/Shader.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Shader);

////////////////////////
///   Constructors   ///

Shader::Shader(const Path& path)
	: Base(path)
{
	_source = TextFile(path).DumpLines();
}
