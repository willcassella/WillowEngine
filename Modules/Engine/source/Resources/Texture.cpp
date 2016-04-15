// Texture.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Engine/Resources/Texture.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Texture);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Texture::Texture(const Path& path)
		: _image{ path }
	{
		// All done
	}
}
