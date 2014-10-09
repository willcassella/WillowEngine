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

		/** Writes the warning message prefix to the console */
		static void PrintWarningPrefix();

		/** Writes the error message prefix to the console */
		static void PrintErrorPrefix();

		/** Writes the input prefix to the console */
		static void PrintInputPrefix();

		/** Returns a string with the users input from the console */
		static String GetInput();

		/** Writes a formatted message to the console, with only one value */
		template <typename FirstType>
		static void PrintFormatted(const String& format, const FirstType& value)
		{
			// Iterate through the format string
			for (const char* character = format.Cstr(); *character != '\0'; ++character)
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

		/** Writes a formatted message to the console, with any number of values */
		template <typename FirstType, typename ... ArgTypes>
		static void PrintFormatted(const String& format, const FirstType& value, const ArgTypes& ... values)
		{
			// Iterate through the format string
			for (const char* character = format.Cstr(); *character != '\0'; ++character)
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

		/** Sends the console caret to the start of the next line */
		static void NewLine();

		/** Writes a value to the console */
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

		/** Writes a value to the console, and then send the caret to the start of the next line */
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

		/** Writes a warning message to the console */
		static void Warning(const String& warning);

		/** Write an error message to the console */
		static void Error(const String& error);

		/** Prompts the user for input from the console, and returns their input */
		static String Prompt(const String& message = "");

		/** Writes a formatted string to the console */
		template <typename ... ArgTypes> 
		static void Write(const String& format, const ArgTypes& ... values)
		{
			Console::PrintFormatted(format, values...);
		}

		/** Writes a formatted string to the console, and returns the caret to the start of the next line */
		template <typename ... ArgTypes> 
		static void WriteLine(const String& format, const ArgTypes& ... values)
		{
			Console::PrintFormatted(format, values...);
			Console::NewLine();
		}

		/** Writes a formatted warning message to the console */
		template <typename ... ArgTypes> 
		static void Warning(const String& format, const ArgTypes& ... values)
		{
			Console::PrintWarningPrefix();
			Console::WriteLine(format, values...);
		}
		
		/** Writes a formatted error message to the console */
		template <typename ... ArgTypes> 
		static void Error(const String& format, const ArgTypes& ... values)
		{
			Console::PrintErrorPrefix();
			Console::WriteLine(format, values...);
		}

		/** Writes a formatted prompt to the console, and returns their input */
		template <typename ... ArgTypes> 
		static String Prompt(const String& format, const ArgTypes& ... values)
		{
			Console::WriteLine(format, values...);
			Console::PrintInputPrefix();
			return Console::GetInput();
		}
	};
}