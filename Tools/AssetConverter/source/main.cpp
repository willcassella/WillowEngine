// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Application.h>
#include <Core/IO/Console.h>
#include "../include/AssetConverter/AssetConversion.h"

int main(int32 argCount, char** args)
{
	using namespace Willow;
	Application::Initialize();

	// If files were passed in via the command line
	if (argCount > 1)
	{
		AssetConversion::Convert(args[1], Array<String>());
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
		AssetConversion::Convert(path, Array<String>());
	}

	Application::Terminate();
}