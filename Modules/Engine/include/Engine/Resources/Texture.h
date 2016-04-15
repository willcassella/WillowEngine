// Texture.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Resource/Resources/Image.h>
#include "../config.h"

namespace willow
{
	struct ENGINE_API Texture final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		Texture(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		FORCEINLINE uint32 get_width() const
		{
			return this->_image.get_width();
		}

		FORCEINLINE uint32 get_height() const
		{
			return this->_image.get_height();
		}

		FORCEINLINE const byte* get_bitmap() const
		{
			return this->_image.get_bitmap();
		}

		////////////////
		///   Data   ///
	private:

		// TODO: Pull this out as a seperate ResourceHandle or something
		Image _image;
	};
}
