// ToArchive.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Operations/ToArchive.h"

namespace Operations
{
	///////////////////////////
	///   Primitive Types   ///

	void ToArchive<bool>::Function(bool value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<char>::Function(char value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<byte>::Function(byte value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<int16>::Function(int16 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<uint16>::Function(uint16 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<int32>::Function(int32 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<uint32>::Function(uint32 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<int64>::Function(int64 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<uint64>::Function(uint64 value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<float>::Function(float value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<double>::Function(double value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<long double>::Function(long double value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<char*>::Function(const char* value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	void ToArchive<const char*>::Function(const char* value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}

	////////////////////////
	///   String Types   ///

	void ToArchive<String>::Function(const String& value, ArchiveWriter& writer)
	{
		writer.SetValue(value);
	}
}
