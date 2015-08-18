// Texture.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Asset.h>
#include <Resource/Resources/Image.h>
#include "../config.h"

class ENGINE_API Texture final : public Asset
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_ASSET
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
		return _width;
	}

	FORCEINLINE uint32 GetHeight() const
	{
		return _height;
	}

	FORCEINLINE const byte* GetBitmap() const
	{
		return _bitmap.GetValue();
	}

	////////////////
	///   Data   ///
private:

	DynamicBuffer _bitmap;
	uint32 _width;
	uint32 _height;
};
