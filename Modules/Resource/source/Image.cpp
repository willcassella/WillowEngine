// Image.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <FreeImage.h>
#include <Core/Console.h>
#include "../include/Resource/Image.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Image);

////////////////////////
///   Constructors   ///

Image::Image(const String& path)
	: Resource(path)
{
	// Open the file
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.Cstr());
	FIBITMAP* image = FreeImage_Load(format, path.Cstr(), 0);

	if (!image)
	{
		Console::Warning("'@' could not be opened", path);
		return;
	}

	FIBITMAP* temp = image;
	_bitmap = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);

	_width = FreeImage_GetWidth(image);
	_height = FreeImage_GetHeight(image);

	Console::WriteLine("'@' loaded successfully", path);
}

Image::~Image()
{
	FreeImage_Unload((FIBITMAP*)_bitmap);
}

///////////////////
///   Methods   ///

uint32 Image::GetWidth() const
{
	return _width;
}

uint32 Image::GetHeight() const
{
	return _height;
}

void* Image::GetBitmap() const
{
	return _bitmap;
}