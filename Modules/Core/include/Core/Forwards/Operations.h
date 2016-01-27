// Operations.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
/** "Operations" are a collection of generic functions that can be performed on polymorphic and non-polymorphic types.
* These functions can see through polymorphism (using the reflection system), so even if the visible type doesn't implement 
* the desired function, it can still be called if the derived type does. */
#pragma once

#include "IO.h"
#include "Containers.h"

/////////////////////
///   Functions   ///

/** Defined in 'Operations/ToString.h' */
template <typename T>
String ToString(const T& value);

/** Defined in 'Operations/ToString.h' */
template <typename T>
String Format(const String& format, const T& value);

/** Defined in 'Operations/ToString.h' */
template <typename T, typename ... MoreT>
String Format(const String& format, const T& value, const MoreT& ... more);

/** Defined in 'Operations/FromString.h' */
template <typename T>
String FromString(T& value, const String& string);

/** Defined in 'Operations/FromString.h' */
template <typename T>
String Parse(const String& string, const String& format, T& value);

/** Defined in 'Operators/FromString' */
template <typename T, typename ... MoreT>
String Parse(const String& string, const String& format, T& value, MoreT& ... more);

/** Defined in 'Operations/ToArchive.h' */
template <typename T>
void ToArchive(const T& value, OutArchive& archive);

/** Defined in 'Operations/FromArchive.h' */
template <typename T>
void FromArchive(T& value, const InArchive& archive);

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** These types are useful for overload resolution when using SFINAE. */
	using Preferred = int;
	using Fallback = char;

	namespace Default
	{
		/** Defined in 'Reflection/TypeInfo.h' */
		template <typename T>
		String ToString(const T& value);

		/** Defined in 'Reflection/TypeInfo.h' */
		template <typename T>
		String FromString(T& value, const String& string);

		/** Defined in 'Reflection/CompoundInfo.h' */
		template <typename T>
		void ToArchive(const T& value, OutArchive& archive);

		/** Defined in 'Reflection/CompoundInfo.h' */
		template <typename T>
		void FromArchive(T& value, const InArchive& archive);
	}
}
