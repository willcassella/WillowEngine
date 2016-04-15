// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Application.h>
#include <Core/IO/Console.h>
#include "../include/AssetConverter/AssetConversion.h"

int main(int argc, char* argv[])
{
	Application::Initialize();

	// If files were passed in via the command line
	if (argc > 1)
	{
		willow::asset_conversion::convert(argv[1], Array<String>());
		return 0;
	}

	Console::WriteLine("---Asset Converter---");
	Console::NewLine();
	Console::WriteLine("Enter the path to a file to convert:");

	while (true)
	{
		willow::Path path = Console::Prompt();
		Console::NewLine();
		 
		if (path.is_empty())
		{
			break;
		}

		// @TODO: Parse options (setting compression level, renaming output)
		willow::asset_conversion::convert(path, Array<String>{});
	}

	Application::Terminate();
}