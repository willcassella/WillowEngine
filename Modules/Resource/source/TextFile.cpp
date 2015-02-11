// TextFile.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <string>
#include <fstream>
#include <Core/Console.h>
#include "../include/Resource/TextFile.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(TextFile);

////////////////////////
///   Constructors   ///

TextFile::TextFile(const String& path)
	: Super(path)
{
	std::ifstream file(path.Cstr(), std::ios::in);
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

const Array<String>& TextFile::GetLines() const
{
	return _lines;
}