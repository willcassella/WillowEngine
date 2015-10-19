// BinaryFile.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <cstdio>
#include "../../include/Resource/Resources/BinaryFile.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(BinaryFile);

////////////////////////
///   Constructors   ///

BinaryFile::BinaryFile(const Path& path)
	: Base(path)
{
	// Create a buffer to hold the contents of the file
	_data.Reset(GetSize());

	// I'm using the standard C api since for some reason C++'s
	// ifstream was unbeleivably slow compared to this (or at least how I was using it)
	FILE* file = fopen(path.ToString().Cstr(), "r");
	fread(_data.GetValue(), sizeof(byte), GetSize(), file);
	fclose(file);
}

///////////////////
///   Methods   ///

const byte* BinaryFile::GetData() const
{
	return _data.GetValue();
}
