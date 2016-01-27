// FromArchive.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../include/Core/Operations/FromArchive.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	///////////////////////////
	///   Primitive Types   ///

	void FromArchive<bool>::Function(bool& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<char>::Function(char& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<byte>::Function(byte& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<int16>::Function(int16& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<uint16>::Function(uint16& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<int32>::Function(int32& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<uint32>::Function(uint32& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<int64>::Function(int64& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<uint64>::Function(uint64& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<float>::Function(float& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<double>::Function(double& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	void FromArchive<long double>::Function(long double& value, const InArchive& archive)
	{
		archive.Get(value);
	}

	////////////////////////
	///   String Types   ///

	void FromArchive<String>::Function(String& value, const InArchive& archive)
	{
		archive.Get(value);
	}
}
