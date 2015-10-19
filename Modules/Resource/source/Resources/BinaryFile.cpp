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
	// Open the file
	std::ifstream file;
	file.open(path.ToString().Cstr(), std::ios::in | std::ios::binary);

	// Make sure the file opened correctly
	if (!file.is_open())
	{
		return;
	}

	// Resize the buffer to hold the file
	_data.Reset(this->GetSize());

	// Read the contents of the file into the buffer
	file.read(_data.GetValueAs<char>(), this->GetSize());

	// Make sure the contents were read correctly
	if (file.gcount() != this->GetSize())
	{
		Console::WriteLine("An error occurred while reading the binary file '@'.", path);
	}

	// Close the file
	file.close();
}

///////////////////
///   Methods   ///

const byte* BinaryFile::GetData() const
{
	return _data.GetValue();
}
