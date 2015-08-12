// Image.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <FreeImage.h>
#include <Core/Console.h>
#include "../../include/Resource/Resources/Image.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Image);

////////////////////////
///   Constructors   ///

Image::Image(const Path& path)
	: Base(path)
{
	// Open the file
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.ToString().Cstr());
	FIBITMAP* image = FreeImage_Load(format, path.ToString().Cstr(), 0);

	if (!image)
	{
		Console::Warning("'@' could not be opened", path);
		return;
	}

	FIBITMAP* temp = image;
	_bitmap = (uint32*)FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(temp);

	_width = FreeImage_GetWidth(image);
	_height = FreeImage_GetHeight(image);

	Console::WriteLine("'@' loaded successfully", path);
}

Image::~Image()
{
	FreeImage_Unload(reinterpret_cast<FIBITMAP*>(_bitmap));
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

const uint32* Image::GetBitmap() const
{
	return _bitmap;
}