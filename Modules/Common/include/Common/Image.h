// Image.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Resource/Resource.h>
#include "config.h"

class COMMON_API Image : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Resource);

	////////////////////////
	///   Constructors   ///
public:

	Image(const String& path);
	~Image() override;

	///////////////////
	///   Methods   ///
public:

	uint32 GetWidth() const;
	uint32 GetHeight() const;
	void* GetBitmap() const;

	////////////////
	///   Data   ///
private:

	void* _bitmap;
	uint32 _width;
	uint32 _height;
};