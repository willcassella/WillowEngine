// Texture.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Asset.h>
#include <Resource/Resources/Image.h>
#include "../config.h"

class ENGINE_API Texture final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Asset)

	////////////////////////
	///   Constructors   ///
public:

	Texture(const Path& path);

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE uint32 GetWidth() const
	{
		return _image.GetWidth();
	}

	FORCEINLINE uint32 GetHeight() const
	{
		return _image.GetHeight();
	}

	FORCEINLINE const byte* GetBitmap() const
	{
		return _image.GetBitmap();
	}

	////////////////
	///   Data   ///
private:

	Image _image;
};
