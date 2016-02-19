// Operations.h - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "IO.h"
#include "Containers.h"

/////////////////
///   Types   ///

namespace Implementation
{
	/** These types are useful for overload resolution when using SFINAE. */
	using Preferred = int;
	using Fallback = char;
}

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
void ToArchive(const T& value, ArchiveWriter& writer);

/** Defined in 'Operations/FromArchive.h' */
template <typename T>
void FromArchive(T& value, const ArchiveReader& reader);

namespace Operations
{
	namespace Default
	{
		/** Defined in 'Reflection/TypeInfo.h' */
		template <typename T>
		String ToString(const T& value);

		/** Defined in 'Reflection/CompoundInfo.h' */
		template <typename T>
		void ToArchive(const T& value, ArchiveWriter& writer);

		/** Defined in 'Reflection/CompoundInfo.h' */
		template <typename T>
		void FromArchive(T& value, const ArchiveReader& reader);
	}
}
