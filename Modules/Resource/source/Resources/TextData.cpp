// TextData.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <string>
#include <fstream>
#include <Core/IO/Console.h>
#include "../../include/Resource/Resources/TextData.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::TextData);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	TextData::TextData(const Path& path)
	{
		std::ifstream file(path.c_str(), std::ios::in);
		std::string line;

		if (!file.is_open())
		{
			return;
		}

		while (std::getline(file, line))
		{
			_lines.Add(line.c_str());
		}
	}

	///////////////////
	///   Methods   ///

	String TextData::dump_lines() const
	{
		String result;

		for (const auto& line : _lines)
		{
			result += line + '\n';
		}

		return result;
	}
}
