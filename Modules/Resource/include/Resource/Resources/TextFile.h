// TextFile.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Resource.h"

class RESOURCE_API TextFile final : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Resource)

	////////////////////////
	///   Constructors   ///
public:

	TextFile(const Path& path);

	///////////////////
	///   Methods   ///
public:

	/** Dumps all lines of the text file into a String (including line endings) */
	String DumpLines() const;

	/** Returns an Array of all the lines in the text file */
	FORCEINLINE const Array<String>& GetLines() const
	{
		return _lines;
	}

	////////////////
	///   Data   ///
private:

	Array<String> _lines;
};