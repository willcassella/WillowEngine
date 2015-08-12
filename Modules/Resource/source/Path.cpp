// Path.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../include/Resource/Path.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Path);

////////////////////////
///   Constructors   ///

Path::Path()
{
	// All done
}

Path::Path(CString path)
	: _path(path)
{
	Sanitize();
}


Path::Path(const String& path)
	: _path(path)
{
	Sanitize();
}

///////////////////
///   Methods   ///

String Path::GetFileExtension() const
{
	auto occurences = _path.OccurencesOf('.');
	if (!occurences.IsEmpty())
	{
		return _path.SubString(occurences.Last() + 1);
	}
	else
	{
		return "";
	}
}

String Path::GetFileName() const
{
	String name = _path;

	auto forwardSlashes = name.OccurencesOf("/");
	auto backSlashes = name.OccurencesOf("\\");

	if (!forwardSlashes.IsEmpty())
	{
		if (!backSlashes.IsEmpty())
		{
			if (forwardSlashes.Last() >= backSlashes.Last())
			{
				name = name.SubString(forwardSlashes.Last());
			}
			else
			{
				name = name.SubString(backSlashes.Last());
			}
		}
		else
		{
			name = name.SubString(forwardSlashes.Last());
		}
	}
	else if (!backSlashes.IsEmpty())
	{
		name = name.SubString(backSlashes.Last());
	}

	auto dots = name.OccurencesOf(".");
	if (!dots.IsEmpty())
	{
		return name.SubString(0, dots.Last());
	}

	return name;
}

void Path::Sanitize()
{
	// TODO: This
}

/////////////////////
///   Operators   ///

Path& Path::operator=(CString path)
{
	_path = path;
	Sanitize();

	return self;
}

Path& Path::operator=(const String& path)
{
	_path = path;
	Sanitize();

	return self;
}
