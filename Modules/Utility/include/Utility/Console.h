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
	public:

		/** Sends the console caret to the start of the next line */
		static void NewLine();

		/** Writes a message to the console */
		static void Write(const String& message);

		/** Writes a message to the console, and then send the caret to the start of the next line */
		static void WriteLine(const String& message);

		/** Writes a warning message to the console */
		static void Warning(const String& warning);

		/** Write an error message to the console */
		static void Error(const String& error);

		/** Prompts the user for input from the console, and returns their input */
		static String Prompt(const String& message = "");

		/** Writes a value to the console */
		template <typename ValueType>
		static inline void Write(const ValueType& value)
		{
			using Willow::ValueToString;
			Console::Write(ValueToString(value));
		}

		/** Writes a formatted string to the console */
		template <typename ... ArgTypes> 
		static inline void Write(const String& format, const ArgTypes& ... values)
		{
			Console::Write(String::Format(format, values...));
		}

		/** Writes a value to the console, and returns the caret to the start of the next line */
		template <typename ValueType>
		static inline void WriteLine(const ValueType& value)
		{
			using Willow::ValueToString;
			Console::WriteLine(ValueToString(value));
		}

		/** Writes a formatted string to the console, and returns the caret to the start of the next line */
		template <typename ... ArgTypes> 
		static inline void WriteLine(const String& format, const ArgTypes& ... values)
		{
			Console::WriteLine(String::Format(format, values...));
		}

		/** Writes a formatted warning message to the console */
		template <typename ... ArgTypes>
		static inline void Warning(const String& format, const ArgTypes& ... values)
		{
			Console::Warning(String::Format(format, values...));
		}
		
		/** Writes a formatted error message to the console */
		template <typename ... ArgTypes> 
		static inline void Error(const String& format, const ArgTypes& ... values)
		{
			Console::Error(String::Format(format, values...));
		}

		/** Writes a formatted prompt to the console, and returns their input */
		template <typename ... ArgTypes>
		static inline String Prompt(const String& format, const ArgTypes& ... values)
		{
			return Console::Prompt(String::Format(format, values...));
		}
	};
}