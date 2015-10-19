// Image.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Resource.h"

class RESOURCE_API Image final : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
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
	const byte* GetBitmap() const;

	////////////////
	///   Data   ///
private:

	const byte* _bitmap;
	uint32 _width;
	uint32 _height;
	void* _image;
};