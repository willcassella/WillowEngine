// Console.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "String.h"

/** Nice wrapper for 'std::cout' and 'std::cin' (because let's face it: using those is ugly as hell) */
namespace Console
{
	////////////////////
	///   Functions  ///

	/** Sends the console caret to the start of the next line */
	CORE_API void NewLine();

	/** Writes a message to the console */
	CORE_API void Write(const String& message);

	/** Writes a message to the console, and then send the caret to the start of the next line */
	CORE_API void WriteLine(const String& message);

	/** Writes a warning message to the console */
	CORE_API void Warning(const String& warning);

	/** Write an error message to the console */
	CORE_API void Error(const String& error);

	/** Prompts the user for input from the console, and returns their input */
	CORE_API String Prompt();

	/** Prompts the user for input from the console with a message, and returns their input */
	CORE_API String Prompt(const String& message);

	/** Writes a value to the console */
	template <typename ValueType>
	inline void Write(const ValueType& value)
	{
		Write(ToString(value));
	}

	/** Writes a formatted String to the console */
	template <typename ... AnyTypes> 
	inline void Write(const String& format, const AnyTypes& ... values)
	{
		Console::Write(String::Format(format, values...));
	}

	/** Writes a value to the console, and returns the caret to the start of the next line */
	template <typename ValueType>
	inline void WriteLine(const ValueType& value)
	{
		WriteLine(ToString(value));
	}

	/** Writes a formatted String to the console, and returns the caret to the start of the next line */
	template <typename ... AnyTypes> 
	inline void WriteLine(const String& format, const AnyTypes& ... values)
	{
		WriteLine(String::Format(format, values...));
	}

	/** Writes a formatted warning message to the console */
	template <typename ... AnyTypes>
	inline void Warning(const String& format, const AnyTypes& ... values)
	{
		Warning(String::Format(format, values...));
	}
		
	/** Writes a formatted error message to the console */
	template <typename ... AnyTypes> 
	inline void Error(const String& format, const AnyTypes& ... values)
	{
		Error(String::Format(format, values...));
	}

	/** Writes a formatted prompt to the console, and returns the user's input */
	template <typename ... AnyTypes>
	inline String Prompt(const String& format, const AnyTypes& ... values)
	{
		return Prompt(String::Format(format, values...));
	}
};