// Shader.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Assets/Shader.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Shader);

////////////////////////
///   Constructors   ///

Shader::Shader(const TextFile& file)
	: Base(file)
{
	// All done
}

///////////////////
///   Methods   ///

void Shader::OnReload()
{
	// Do nothing
}
