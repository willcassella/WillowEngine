// Image.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Resource.h"
#include "../Reflection/ResourceInfo.h"

class RESOURCE_API Image final : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_RESOURCE
	EXTENDS(Resource)

	////////////////////////
	///   Constructors   ///
public:

	Image(const Path& path);
	~Image() override;

	///////////////////
	///   Methods   ///
public:

	uint32 GetWidth() const;
	uint32 GetHeight() const;
	const uint32* GetBitmap() const;

	////////////////
	///   Data   ///
private:

	uint32* _bitmap;
	uint32 _width;
	uint32 _height;
};