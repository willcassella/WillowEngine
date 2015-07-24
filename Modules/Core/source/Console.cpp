// Console.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <iostream>
#include "../include/Core/Console.h"

const uint32 MaxInput = 256; // Max number of characters retrieved from one line of input
bool EmptyLine = true; // Whether the current line is empty
bool EmptyLineAbove = true; // Whether the line above is empty
CString WarningPrefix = "WARNING: "; // String printed before every warning
CString ErrorPrefix = "ERROR: "; // String printed before every error
CString PromptPrefix = "> "; // String printed before every input

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

void Console::Write(CString message)
{
	static bool firstWrite = true;

	if (firstWrite)
	{
		NewLine();
		firstWrite = false;
	}

	std::cout << message;
	EmptyLine = false;
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

String GetUserInput()
{
	char input[MaxInput];
	std::cin.getline(input, MaxInput);
	return String(input);
}

String Console::Prompt()
{
	NewLine();

	if (!EmptyLineAbove)
	{
		NewLine();
	}

	Write(PromptPrefix);
	String input = GetUserInput();
	NewLine();
	return input;
}

String Console::Prompt(CString message)
{
	WriteLine(message);
	return Prompt();
}