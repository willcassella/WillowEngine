// Image.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <FreeImage.h>
#include <Core/Console.h>
#include "../../include/Resource/Resources/Image.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Image);

////////////////////////
///   Constructors   ///

Image::Image(const Path& path)
	: Base(path), _bitmap(nullptr), _width(0), _height(0), _image(nullptr)
{
	// Open the file
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.ToString().Cstr());
	FIBITMAP* image = FreeImage_Load(format, path.ToString().Cstr(), 0);

	if (!image)
	{
		Console::Warning("'@' could not be opened", path);
		return;
	}

	// Convert the image to 32 bits
	{
		FIBITMAP* temp = image;
		image = FreeImage_ConvertTo32Bits(image);
		FreeImage_Unload(temp);
	}

	_bitmap = FreeImage_GetBits(image);
	_width = FreeImage_GetWidth(image);
	_height = FreeImage_GetHeight(image);
	_image = image;

	Console::WriteLine("'@' loaded successfully", path);
}

Image::~Image()
{
	FreeImage_Unload(static_cast<FIBITMAP*>(_image));
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

const byte* Image::GetBitmap() const
{
	return _bitmap;
}