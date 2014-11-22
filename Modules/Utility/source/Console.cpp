// Console.cpp

#include <iostream>
#include "../include/Utility/Console.h"
using namespace Willow;

#define MAX_INPUT_SIZE 256

///////////////////
///   Methods   ///

void Console::NewLine()
{
	std::cout << std::endl << " ";
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
}

void Console::WriteLine(const String& message)
{
	Console::Write(message);
	Console::NewLine();
}

void Console::Warning(const String& warning)
{
	Console::Write("WARNING: ");
	Console::WriteLine(warning);
}

void Console::Error(const String& error)
{
	Console::Write("ERROR: ");
	Console::WriteLine(error);
}

String Console::Prompt(const String& message)
{
	Console::WriteLine(message);
	Console::Write("> ");
	char input[MAX_INPUT_SIZE];
	std::cin.getline(input, MAX_INPUT_SIZE);
	return input;
}