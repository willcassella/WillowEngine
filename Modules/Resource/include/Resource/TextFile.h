// TextFile.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "SystemResource.h"

class RESOURCE_API TextFile : public SystemResource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(SystemResource);

	////////////////////////
	///   Constructors   ///
public:

	TextFile(const String& path);
	TextFile(const TextFile& copy) = delete;
	TextFile(TextFile&& move) = delete;

	///////////////////
	///   Methods   ///
public:

	/** Dumps all lines of the text file into a String (including line endings) */
	String DumpLines() const;

	/** Returns an Array of all the lines in the text file */
	const Array<String>& GetLines() const;

	/////////////////////
	///   Operators   ///
public:

	TextFile& operator=(const TextFile& copy) = delete;
	TextFile& operator=(TextFile&& move) = delete;

	////////////////
	///   Data   ///
private:

	Array<String> _lines;
};