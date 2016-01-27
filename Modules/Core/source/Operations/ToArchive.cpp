// ToArchive.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Operations/ToArchive.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///////////////////////////
	///   Primitive Types   ///

	void ToArchive<bool>::Function(bool value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<char>::Function(char value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<byte>::Function(byte value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<int16>::Function(int16 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<uint16>::Function(uint16 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<int32>::Function(int32 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<uint32>::Function(uint32 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<int64>::Function(int64 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<uint64>::Function(uint64 value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<float>::Function(float value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<double>::Function(double value, OutArchive& archive)
	{
		archive.Set(value);
	}

	void ToArchive<long double>::Function(long double value, OutArchive& archive)
	{
		archive.Set(value);
	}

	////////////////////////
	///   String Types   ///

	void ToArchive<String>::Function(const String& value, OutArchive& archive)
	{
		archive.Set(value);
	}
}
