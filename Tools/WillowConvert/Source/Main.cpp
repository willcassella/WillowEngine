// Main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** This program converts text files to .DAT for faster loading by the engine */

#include <Core/Console.h>
#include "../include/WillowConvert/WillowConvert.h"

int main(int32 argCount, char** args)
{
	// If files were passed in
	if (argCount > 1)
	{
		WillowConvert::Convert(args[1], List<String>());
		return 0;
	}

	Console::WriteLine("---WillowConvert---");
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
		WillowConvert::Convert(path, List<String>());
	}

	return 0;
}