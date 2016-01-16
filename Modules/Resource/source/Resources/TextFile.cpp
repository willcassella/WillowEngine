// TextFile.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <string>
#include <fstream>
#include <Core/IO/Console.h>
#include "../../include/Resource/Resources/TextFile.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(TextFile);

////////////////////////
///   Constructors   ///

TextFile::TextFile(const Path& path)
	: Base(path)
{
	std::ifstream file(path.ToString().Cstr(), std::ios::in);
	std::string line;

	if (!file.is_open())
	{
		Console::Warning("'@' could not be opened", path);
		file.close();
		return;
	}

	while (std::getline(file, line))
	{
		_lines.Add(line.c_str());
	}

	file.close();
	Console::WriteLine("'@' loaded successfully", path);
}

///////////////////
///   Methods   ///

String TextFile::DumpLines() const
{
	String result;

	for (const String& line : _lines)
	{
		result += line + '\n';
	}

	return result;
}
