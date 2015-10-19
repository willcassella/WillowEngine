// Texture.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Assets/Texture.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Texture);

////////////////////////
///   Constructors   ///

Texture::Texture(const Path& path)
	: Base(path), _image(path)
{
	// All done
}
