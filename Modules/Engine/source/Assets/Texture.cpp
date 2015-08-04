// Texture.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Assets/Texture.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Texture);

////////////////////////
///   Constructors   ///

Texture::Texture(const Image& image)
	: Base(image)
{
	// All done
}

///////////////////
///   Methods   ///

void Texture::OnReload()
{
	// Do nothing
}
