// Image.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Umbrellas/Reflection.h>
#include "../Path.h"

namespace willow
{
	struct RESOURCE_API Image final	
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:
		
		Image();
		Image(const Path& path);
		Image(const Image& copy);
		Image(Image&& move);
		~Image();

		///////////////////
		///   Methods   ///
	public:

		/** Returns the width of this Image. */
		uint32 get_width() const;
		
		/** Returns the height of this Image. */
		uint32 get_height() const;
		
		/** Returns a pointer to the bitmap data for this Image. */
		const byte* get_bitmap() const;

		/////////////////////
		///   Operators   ///
	public:

		Image& operator=(const Image& copy);
		Image& operator=(Image&& move);

		////////////////
		///   Data   ///
	private:

		struct FIBITMAP* _bitmap;
	};
}