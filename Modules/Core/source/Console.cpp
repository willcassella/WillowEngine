// Console.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <iostream>
#include "../include/Core/Console.h"

const uint32 MaxInput = 256; // Max number of characters retrieved from one line of input
bool EmptyLine = true; // Whether the current line is empty
bool EmptyLineAbove = true; // Whether the line above is empty
const String WarningPrefix = "WARNING: "; // String printed before every warning
const String ErrorPrefix = "ERROR: "; // String printed before every error
const String PromptPrefix = "> "; // String printed before every input

////////////////////
///   Functions  ///

void Console::NewLine()
{
	std::cout << std::endl << " ";

	if (EmptyLine)
	{
		EmptyLineAbove = true;
	}
	else
	{
		EmptyLineAbove = false;
	}

	EmptyLine = true;
}

void Console::Write(const String& message)
{
	static bool firstWrite = true;

	if (firstWrite)
	{
		Console::NewLine();
		firstWrite = false;
	}

	std::cout << message.Cstr();
	EmptyLine = false;
}

void Console::WriteLine(const String& message)
{
	Console::Write(message);
	Console::NewLine();
}

void Console::Warning(const String& warning)
{
	Console::Write(String(WarningPrefix));
	Console::WriteLine(warning);
}

void Console::Error(const String& error)
{
	Console::Write(ErrorPrefix);
	Console::WriteLine(error);
}

String GetUserInput()
{
	char input[MaxInput];
	std::cin.getline(input, MaxInput);
	return String(input);
}

String Console::Prompt()
{
	Console::NewLine();

	if (!EmptyLineAbove)
	{
		Console::NewLine();
	}

	Console::Write(PromptPrefix);
	String input = GetUserInput();
	Console::NewLine();
	return input;
}

String Console::Prompt(const String& message)
{
	Console::WriteLine(message);
	return Console::Prompt();
}