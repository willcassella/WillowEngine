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
	std::cout << message;
}

void Console::Write(bool value)
{
	std::cout << value;
}

void Console::Write(char value)
{
	std::cout << value;
}

void Console::Write(byte value)
{
	std::cout << value;
}

void Console::Write(int16 value)
{
	std::cout << value;
}

void Console::Write(uint16 value)
{
	std::cout << value;
}

void Console::Write(int32 value)
{
	std::cout << value;
}

void Console::Write(uint32 value)
{
	std::cout << value;
}

void Console::Write(int64 value)
{
	std::cout << value;
}

void Console::Write(uint64 value)
{
	std::cout << value;
}

void Console::Write(float value)
{
	std::cout << value;
}

void Console::Write(double value)
{
	std::cout << value;
}

void Console::Write(long double value)
{
	std::cout << value;
}

void Console::WriteLine(CString message)
{
	Write(message);
	NewLine();
}

void Console::WriteLine(bool value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(char value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(byte value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(int16 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(uint16 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(int32 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(uint32 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(int64 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(uint64 value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(float value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(double value)
{
	Write(value);
	NewLine();
}

void Console::WriteLine(long double value)
{
	Write(value);
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
