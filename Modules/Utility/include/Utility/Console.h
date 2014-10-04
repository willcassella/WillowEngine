// Console.h
#pragma once

#include "String.h"

namespace Willow
{
	class UTILITY_API Console
	{
		////////////////////////
		///   Constructors   ///
	private:

		Console() = delete;

		///////////////////
		///   Methods   ///
	private:

		static void PrintWarningPrefix();
		static void PrintErrorPrefix();
		static void PrintInputPrefix();
		static String GetInput();

		template <typename FirstType>
		static void PrintFormatted(const String& format, const FirstType& value)
		{
			// Iterate through the rest of the format string
			for (const char* character = format.Cstr(); *character != '\0'; character++)
			{
				// If we hit the placeholder character
				if (*character == '@')
				{
					// Print the value and the rest of the string
					Console::Write(value);
					Console::Write(character + 1);
					return;
				}
				else
				{
					// Print whatever character we're at
					Console::Write(*character);
				}
			}
		}

		template <typename FirstType, typename ... ArgTypes>
		static void PrintFormatted(const String& format, const FirstType& value, const ArgTypes& ... values)
		{
			// Iterate through the format string
			for (const char* character = format.Cstr(); *character != '\0'; character++)
			{
				// If we hit the placeholder character
				if (*character == '@')
				{
					// Print the value and recursively print the rest of the string;
					Console::Write(value);
					return PrintFormatted(character + 1, values...);
				}
				else
				{
					// Print whatever character we're at
					Console::Write(*character);
				}
			}
		}

	public:

		static void NewLine();
		static void Write(const String& message);
		static void Write(char value);
		static void Write(int16 value);
		static void Write(int32 value);
		static void Write(int64 value);
		static void Write(byte value);
		static void Write(uint16 value);
		static void Write(uint32 value);
		static void Write(float value);
		static void Write(double value);
		static void WriteLine(const String& message);
		static void WriteLine(char value);
		static void WriteLine(int16 value);
		static void WriteLine(int32 value);
		static void WriteLine(int64 value);
		static void WriteLine(byte value);
		static void WriteLine(uint16 value);
		static void WriteLine(uint32 value);
		static void WriteLine(float value);
		static void WriteLine(double value);
		static void Warning(const String& warning);
		static void Error(const String& error);
		static String Prompt(const String& message = "");

		template <typename ... ArgTypes> 
		static void Write(const String& format, const ArgTypes& ... values)
		{
			Console::PrintFormatted(format, values...);
		}

		template <typename ... ArgTypes> 
		static void WriteLine(const String& format, const ArgTypes& ... values)
		{
			Console::PrintFormatted(format, values...);
			Console::NewLine();
		}

		template <typename ... ArgTypes> 
		static void Warning(const String& format, const ArgTypes& ... values)
		{
			Console::PrintWarningPrefix();
			Console::WriteLine(format, values...);
		}
		
		template <typename ... ArgTypes> 
		static void Error(const String& format, const ArgTypes& ... values)
		{
			Console::PrintErrorPrefix();
			Console::WriteLine(format, values...);
		}

		template <typename ... ArgTypes> 
		static String Prompt(const String& format, const ArgTypes& ... values)
		{
			Console::WriteLine(format, values...);
			Console::PrintInputPrefix();
			return Console::GetInput();
		}
	};
}