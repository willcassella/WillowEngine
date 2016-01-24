// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include "../include/AssetConverter/AssetConverter.h"

int main(int32 argCount, char** args)
{
	Application::Initialize();

	// If files were passed in via the command line
	if (argCount > 1)
	{
		AssetConverter::Convert(args[1], Array<String>());
		return 0;
	}

	Console::WriteLine("---Asset Converter---");
	Console::NewLine();
	Console::WriteLine("Enter the path to a file to convert:");

	while (true)
	{
		String path = Console::Prompt();
		Console::NewLine();
		 
		if (path.IsEmpty())
		{
			break;
		}

		// @TODO: Parse options (setting compression level, renaming output)
		AssetConverter::Convert(path, Array<String>());
	}

	Application::Terminate();
}