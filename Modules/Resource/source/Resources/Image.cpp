// Image.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <FreeImage.h>
#include <Core/IO/Console.h>
#include "../../include/Resource/Resources/Image.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Image);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Image::Image()
		: _bitmap{ nullptr }
	{
		// All done
	}

	Image::Image(const Path& path)
	{
		// Open the file
		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str());
		FIBITMAP* image = FreeImage_Load(format, path.c_str(), 0);

		if (!image)
		{
			return;
		}

		// Convert the image to 32 bits
		{
			FIBITMAP* temp = image;
			image = FreeImage_ConvertTo32Bits(image);
			FreeImage_Unload(temp);
		}

		this->_bitmap = image;
	}

	Image::Image(const Image& copy)
		: _bitmap{ FreeImage_Clone(copy._bitmap) }
	{
		// All done
	}

	Image::Image(Image&& move)
		: _bitmap{ move._bitmap }
	{
		move._bitmap = nullptr;
	}

	Image::~Image()
	{
		FreeImage_Unload(this->_bitmap);
	}

	///////////////////
	///   Methods   ///

	uint32 Image::get_width() const
	{
		return FreeImage_GetWidth(this->_bitmap);
	}

	uint32 Image::get_height() const
	{
		return FreeImage_GetHeight(this->_bitmap);
	}

	const byte* Image::get_bitmap() const
	{
		return FreeImage_GetBits(this->_bitmap);
	}

	/////////////////////
	///   Operators   ///

	Image& Image::operator=(const Image& copy)
	{
		if (this != &copy)
		{
			FreeImage_Unload(this->_bitmap);
			this->_bitmap = FreeImage_Clone(copy._bitmap);
		}

		return *this;
	}

	Image& Image::operator=(Image&& move)
	{
		if (this != &move)
		{
			FreeImage_Unload(this->_bitmap);
			this->_bitmap = move._bitmap;
			move._bitmap = nullptr;
		}

		return *this;
	}
}
