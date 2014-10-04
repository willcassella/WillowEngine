// Console.cpp

#include <iostream>
#include <string>
#include <cstdarg>
#include "..\include\Utility\Console.h"
using namespace Willow;

#define MAX_INPUT_SIZE 256

///////////////////
///   Methods   ///

void Console::PrintWarningPrefix()
{
	Console::Write("WARNING: ");
}

void Console::PrintErrorPrefix()
{
	Console::Write("ERROR: ");
}

void Console::PrintInputPrefix()
{
	Console::Write("  > ");
}

String Console::GetInput()
{
	char* input = new char[MAX_INPUT_SIZE];
	std::cin.getline(input, MAX_INPUT_SIZE);
	String str = input;
	delete[] input;
	return str;
}

void Console::NewLine()
{
	std::cout << std::endl;
}

void Console::Write(const String& message)
{
	std::cout << message.Cstr();
}

void Console::Write(char value)
{
	std::cout << value;
}

void Console::Write(int16 value)
{
	std::cout << value;
}

void Console::Write(int32 value)
{
	std::cout << value;
}

void Console::Write(int64 value)
{
	std::cout << value;
}

void Console::Write(byte value)
{
	std::cout << value;
}

void Console::Write(uint16 value)
{
	std::cout << value;
}

void Console::Write(uint32 value)
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

void Console::WriteLine(const String& message)
{
	Console::Write(message);
	Console::NewLine();
}

void Console::WriteLine(char value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(int16 value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(int32 value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(int64 value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(byte value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(uint16 value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(uint32 value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(float value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::WriteLine(double value)
{
	Console::Write(value);
	Console::NewLine();
}

void Console::Warning(const String& warning)
{
	Console::PrintWarningPrefix();
	Console::WriteLine(warning);
}

void Console::Error(const String& error)
{
	Console::PrintErrorPrefix();
	Console::WriteLine(error);
}

String Console::Prompt(const String& message)
{
	Console::WriteLine(message);
	Console::PrintInputPrefix();
	return Console::GetInput();
}