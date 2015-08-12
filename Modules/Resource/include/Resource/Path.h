// Path.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

struct RESOURCE_API Path final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	Path();
	Path(CString path);
	Path(const String& path);

	///////////////////
	///   Methods   ///
public:

	/** If the given String represents a path to a file, this parses and returns the file extension */
	String GetFileExtension() const;

	/** If the given String represents a path to a file, this parses and returns the name of the file */
	String GetFileName() const;

	/** Returns this Path as a String. */
	const String& ToString() const
	{
		return _path;
	}

private:

	/** Makes sure this path has a valid scope. */
	void Sanitize();

	/////////////////////
	///   Operators   ///
public:

	Path& operator=(CString path);
	Path& operator=(const String& path);
	operator const String&() const
	{
		return _path;
	}
	friend FORCEINLINE bool operator==(const Path& lhs, const String& rhs)
	{
		return lhs._path == rhs;
	}
	friend FORCEINLINE bool operator==(const String& lhs, const Path& rhs)
	{
		return rhs == lhs;
	}
	friend FORCEINLINE bool operator!=(const Path& lhs, const String& rhs)
	{
		return !(lhs == rhs);
	}
	friend FORCEINLINE bool operator!=(const String& lhs, const Path& rhs)
	{
		return rhs != lhs;
	}

	////////////////
	///   Data   ///
private:

	String _path;
};
