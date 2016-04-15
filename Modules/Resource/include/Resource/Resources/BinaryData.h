// BinaryData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Path.h"

namespace willow
{
	class RESOURCE_API BinaryData final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		/** Loads from a file. */
		BinaryData(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		byte* get_data();

		const byte* get_data() const;

		std::size_t get_size() const;

		/////////////////
		///   Data   ///
	private:

		DynamicBuffer _data;
	};
}
