// BinaryData.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <sys/stat.h>
#include <fstream>
#include "../../include/Resource/Resources/BinaryData.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::BinaryData);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	BinaryData::BinaryData(const Path& path)
	{
		// Figure out the size of the file
		struct stat fileStats;
		stat(path.c_str(), &fileStats);
		const auto size = fileStats.st_size;

		// Open the file
		std::ifstream file;
		file.open(path.c_str(), std::ios::in | std::ios::binary);

		// Make sure the file opened correctly
		if (!file.is_open())
		{
			return;
		}

		// Resize the buffer to hold the file
		this->_data.reset(size);

		// Read the contents of the file into the buffer
		file.read(this->_data.get_pointer<char>(), size);

		// Make sure the contents were read correctly
		if (file.gcount() != size)
		{
			Console::WriteLine("An error occurred while reading the binary file '@'.", path);
		}
	}

	///////////////////
	///   Methods   ///

	byte* BinaryData::get_data()
	{
		return this->_data.get_pointer();
	}

	const byte* BinaryData::get_data() const
	{
		return this->_data.get_pointer();
	}

	std::size_t BinaryData::get_size() const
	{
		return this->_data.get_size();
	}
}
