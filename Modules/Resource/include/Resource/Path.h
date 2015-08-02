// Path.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

struct RESOURCE_API Path final
{
	////////////////////////
	///   Constructors   ///
public:

	Path(String path)
		: _path(std::move(path))
	{
		// All done TODO: Sanitation
	}

	///////////////////
	///   Methods   ///
public:

	/** If the given String represents a path to a file, this parses and returns the file extension */
	String GetFileExtension() const;

	/** If the given String represents a path to a file, this parses and returns the name of the file */
	String GetFileName() const;

	/////////////////////
	///   Operators   ///
public:

	Path& operator=(String path)
	{
		_path = std::move(path);
		return self;
	}

	////////////////
	///   Data   ///
private:

	String _path;
};
