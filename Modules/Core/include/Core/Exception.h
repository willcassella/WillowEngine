// Exception.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <exception>
#include "Operations/ToString.h"

/** Export the 'std::exception' class as part of the Core module.
* Fixes warning on MSVC. */
#ifdef _MSC_VER
class CORE_API std::exception;
#endif

/** Base class for exceptions. */
class CORE_API Exception : public std::exception
{
	////////////////////////
	///   Constructors   ///
public:

	/** Creates an exception with the error message. */
	Exception(String message);

	/** Creates an exception with a formatted error message. */
	template <typename ... T>
	Exception(const String& format, const T& ... args)
		: Exception{ Format(format, args...) }
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Converts this Exception to a String. */
	const String& ToString() const noexcept
	{
		return this->GetMessage();
	}

	/** Returns a String message containing the details of the exception. */
	const String& GetMessage() const noexcept
	{
		return _message;
	}

	/** Implementation of the 'std::exception' interface. */
	const char* what() const noexcept final override
	{
		return this->GetMessage().Cstr();
	}

	////////////////
	///   Data   ///
private:

	String _message;
};
