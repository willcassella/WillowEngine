// BinaryFile.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <fstream>
#include "../../include/Resource/Resources/BinaryFile.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(BinaryFile);

////////////////////////
///   Constructors   ///

BinaryFile::BinaryFile(const Path& path)
	: Base(path)
{
	// Get the size of the file
	_data.Reset(GetSize());

	// Open a file reader
	std::basic_ifstream<byte> file;
	file.open(path.ToString().Cstr(), std::ios::binary | std::ios::in);

	// Read the data from the file
	file.read(_data.GetValue(), _data.GetSize());

	// Close the file
	file.close();
}

///////////////////
///   Methods   ///

const byte* BinaryFile::GetData() const
{
	return _data.GetValue();
}
