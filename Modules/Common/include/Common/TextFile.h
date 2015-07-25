// TextFile.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Resource/Resource.h>
#include "config.h"

class COMMON_API TextFile : public Resource
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Resource);

	////////////////////////
	///   Constructors   ///
public:

	TextFile(const String& path);

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