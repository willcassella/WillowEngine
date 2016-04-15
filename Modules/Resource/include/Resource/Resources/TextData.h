// TextData.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Path.h"

namespace willow
{
	struct RESOURCE_API TextData final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		/** Loads from a file. */
		TextData(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		/** Dumps all lines of the text file into a String (including line endings) */
		String dump_lines() const;

		/** Returns an Array of all the lines in the text file */
		FORCEINLINE const Array<String>& get_lines() const
		{
			return this->_lines;
		}

		////////////////
		///   Data   ///
	private:

		Array<String> _lines;
	};
}
