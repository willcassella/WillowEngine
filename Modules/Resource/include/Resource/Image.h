// Image.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "Resource.h"

class RESOURCE_API Image : public Resource
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
	Image(const Image& copy) = delete;
	Image(Image&& other) = delete;
	~Image() override;

	///////////////////
	///   Methods   ///
public:

	uint32 GetWidth() const;
	uint32 GetHeight() const;
	void* GetBitmap() const;

	/////////////////////
	///   Operators   ///
public:

	Image& operator=(const Image& copy) = delete;
	Image& operator=(Image&& other) = delete;

	////////////////
	///   Data   ///
private:

	void* _bitmap;
	uint32 _width;
	uint32 _height;
};