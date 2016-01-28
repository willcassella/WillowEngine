// FromArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../IO/ArchiveReader.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'FromArchive'. */
	template <typename T>
	struct FromArchive final
	{
	private:

		/** Implementation for if the type defines its own 'FromArchive' function (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, F& value, const ArchiveReader& reader) -> decltype(value.F::FromArchive(reader))
		{
			return value.FromArchive(reader);
		}

		/** Implementation for if the type does not define its own 'FromArchive' function (fallback). */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, F& value, const ArchiveReader& reader) -> void
		{
			Default::FromArchive(value, reader);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(T& value, const ArchiveReader& reader)
		{
			Impl(0, value, reader);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'FromArchive' for bool. */
	template <>
	struct CORE_API FromArchive < bool > final
	{
		static void Function(bool& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for char. */
	template <>
	struct CORE_API FromArchive < char > final
	{
		static void Function(char& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for byte. */
	template <>
	struct CORE_API FromArchive < byte > final
	{
		static void Function(byte& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for int16. */
	template <>
	struct CORE_API FromArchive < int16 > final
	{
		static void Function(int16& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for uint16. */
	template <>
	struct CORE_API FromArchive < uint16 > final
	{
		static void Function(uint16& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for int32. */
	template <>
	struct CORE_API FromArchive < int32 > final
	{
		static void Function(int32& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for uint32. */
	template <>
	struct CORE_API FromArchive < uint32 > final
	{
		static void Function(uint32& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for int64. */
	template <>
	struct CORE_API FromArchive < int64 > final
	{
		static void Function(int64& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for uint64. */
	template <>
	struct CORE_API FromArchive < uint64 > final
	{
		static void Function(uint64& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for float. */
	template <>
	struct CORE_API FromArchive < float > final
	{
		static void Function(float& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for double. */
	template <>
	struct CORE_API FromArchive < double > final
	{
		static void Function(double& value, const ArchiveReader& reader);
	};

	/** Implementation of 'FromArchive' for long double. */
	template <>
	struct CORE_API FromArchive < long double > final
	{
		static void Function(long double& value, const ArchiveReader& reader);
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'FromArchive' for String. */
	template <>
	struct CORE_API FromArchive < String > final
	{
		static void Function(String& value, const ArchiveReader& reader);
	};
}

/////////////////////
///   Functions   ///

/** TODO: Documentation */
template <typename T>
FORCEINLINE void FromArchive(T& value, const ArchiveReader& reader)
{
	Implementation::FromArchive<T>::Function(value, reader);
}
