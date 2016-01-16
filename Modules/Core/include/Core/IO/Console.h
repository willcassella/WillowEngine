// Console.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../Containers/String.h"

namespace Console
{
	/** Sends the console caret to the start of the next line. */
	CORE_API void NewLine();

	/** Writes a message to the console. */
	CORE_API void Write(CString message);

	/** Writes a message to the console. */
	FORCEINLINE void Write(const String& message)
	{
		Write(message.Cstr());
	}

	/** Writes a message to the console, and then sends the caret to the start of the next line. */
	CORE_API void WriteLine(CString message);

	/** Writes a message to the console, and then sends the caret to the start of the next line. */
	FORCEINLINE void WriteLine(const String& message)
	{
		WriteLine(message.Cstr());
	}

	/** Writes a warning message to the console. */
	CORE_API void Warning(CString warning);

	/** Writes a warning message to the console. */
	FORCEINLINE void Warning(const String& warning)
	{
		Warning(warning.Cstr());
	}

	/** Writes an Error message to the console. */
	CORE_API void Error(CString error);

	/** Write an error message to the console. */
	FORCEINLINE void Error(const String& error)
	{
		Error(error.Cstr());
	}

	/** Prompts the user for input from the console, and returns their input. */
	CORE_API String Prompt();

	/** Prompts the user for input from the console with a message, and returns their input. */
	CORE_API String Prompt(CString message);

	/** Prompts the user for input from the console with a message, and returns their input. */
	FORCEINLINE String Prompt(const String& message)
	{
		return Prompt(message.Cstr());
	}

	/** Writes a value to the console. */
	template <typename T>
	FORCEINLINE void Write(const T& value)
	{
		Write(ToString(value));
	}

	/** Writes a formatted String to the console. */
	template <typename ... T>
	FORCEINLINE void Write(const String& format, const T& ... values)
	{
		Write(Format(format, values...));
	}

	/** Writes a value to the console, and returns the caret to the start of the next line. */
	template <typename T>
	FORCEINLINE void WriteLine(const T& value)
	{
		WriteLine(ToString(value));
	}

	/** Writes a formatted String to the console, and returns the caret to the start of the next line. */
	template <typename ... T>
	FORCEINLINE void WriteLine(const String& format, const T& ... values)
	{
		WriteLine(Format(format, values...));
	}

	/** Writes a formatted warning message to the console. */
	template <typename ... T>
	FORCEINLINE void Warning(const String& format, const T& ... values)
	{
		Warning(Format(format, values...));
	}
	
	/** Writes a formatted error message to the console. */
	template <typename ... T>
	FORCEINLINE void Error(const String& format, const T& ... values)
	{
		Error(Format(format, values...));
	}

	/** Writes a formatted prompt to the console, and returns the user's input. */
	template <typename ... T>
	FORCEINLINE String Prompt(const String& format, const T& ... values)
	{
		return Prompt(Format(format, values...));
	}
}
