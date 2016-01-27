// Console.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <iostream>
#include "../../include/Core/IO/Console.h"

constexpr uint32 MaxInput = 256; // Max number of characters retrieved from one line of input
constexpr CString WarningPrefix = "WARNING: "; // String printed before every warning
constexpr CString ErrorPrefix = "ERROR: "; // String printed before every error
constexpr CString PromptPrefix = "> "; // String printed before every input

////////////////////
///   Functions  ///

void Console::NewLine()
{
	std::cout << std::endl;
}

void Console::Write(CString message)
{
	static bool firstWrite = true;

	if (firstWrite)
	{
		// For some reason this needs to be constructed, otherwise printing upon starting (ie, pre-main) on linux will
		// occasionally fail completely.
		std::ios_base::Init initializer;
		NewLine();
		firstWrite = false;
	}

	std::cout << message;
}

void Console::WriteLine(CString message)
{
	Write(message);
	NewLine();
}

void Console::Warning(CString warning)
{
	Write(WarningPrefix);
	WriteLine(warning);
}

void Console::Error(CString error)
{
	Write(ErrorPrefix);
	WriteLine(error);
}

String Console::Prompt()
{
	Write(PromptPrefix);

	char input[MaxInput];
	std::cin.getline(input, MaxInput);
	return String(input);
}

String Console::Prompt(CString message)
{
	Write(message);
	return Prompt();
}
