// Operations.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** "Operations" are a collection of generic functions that can be performed on polymorphic and non-polymorphic types.
* These functions can see through polymorphism (using the reflection system), so even if the visible type doesn't implement 
* the desired function, it can still be called if the derived type does. */
#pragma once

#include "../config.h"
#include "Core.h"
#include "Memory.h"

/////////////////////
///   Functions   ///

/** Defined in 'Operations/TypeOps.h' */
template <typename T, typename ... Args>
bool Construct(byte* location, Args&& ... args);

/** Defined in 'Operations/TypeOps.h' */
template <typename T, typename ... Args>
NewPtr<T> Construct(Args&& ... args);

/** Defined in 'Reflection/TypeInfo.h' */
template <typename T>
bool Copy(byte* location, T&& value);

/** Defined in 'Reflection/TypeInfo.h' */
template <typename T>
NewPtr<T> Copy(T&& value);

/** Defined in 'Reflection/TypeInfo.h' */
template <typename T, typename F>
bool Assign(T& lhs, F&& rhs);

/** Defined in 'Operations/TypeOps.h' */
template <typename T>
bool Destroy(T& value);

/** Defined in 'Reflection/TypeInfo.h' */
template <typename T>
String ToString(const T& value);

/** Defined in 'Operations/ToString.h' */
template <typename T>
String ToString(const String& format, const T& value);

/** Defined in 'Operations/ToString.h' */
template <typename T, typename ... MoreT>
String ToString(const String& format, const T& first, const MoreT& ... values);

/** Defined in 'Reflection/TypeInfo.h' */
template <typename T>
String FromString(const String& string, T& value);

/** Defined in 'Operations/FromString.h' */
template <typename T>
String FromString(const String& string, const String& format, T& value);

/** Defined in 'Operations/FromString.h' */
template <typename T, typename ... MoreT>
String FromString(const String& string, const String& format, T& first, MoreT& ... values);

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** These types are useful for overload resolution when using SFINAE. */
	using Preferred = int;
	using Fallback = char;
}
