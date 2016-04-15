// Path.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <sys/stat.h>
#include "../include/Resource/Path.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Path);

namespace willow
{
	///////////////////
	///   Methods   ///

	void Path::ToArchive(ArchiveWriter& writer) const
	{
		writer.SetValue(this->_path);
	}

	void Path::FromArchive(const ArchiveReader& reader)
	{
		reader.GetValue(this->_path);
		this->sanitize();
	}

	String Path::get_file_extension() const
	{
		const auto occurences = this->_path.OccurencesOf('.');
		if (!occurences.IsEmpty())
		{
			return this->_path.SubString(occurences.Last() + 1);
		}
		else
		{
			return "";
		}
	}

	String Path::get_file_name() const
	{
		auto name = this->_path;

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

	bool Path::is_empty() const
	{
		return this->_path.IsEmpty();
	}

	bool Path::points_to_file() const
	{
		struct stat fileStats;
		
		if (stat(this->_path.Cstr(), &fileStats) == -1)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void Path::sanitize()
	{
		// TODO: This
	}
}
