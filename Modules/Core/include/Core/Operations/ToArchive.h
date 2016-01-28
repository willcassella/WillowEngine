// ToArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../IO/ArchiveWriter.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'ToArchive' */
	template <typename T>
	struct ToArchive final
	{
	private:

		/** Implementation for types that define their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, const F& value, ArchiveWriter& writer) -> decltype(value.F::ToArchive(writer))
		{
			return value.ToArchive(writer);
		}

		/** Implementation for types that do not defined their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, const F& value, ArchiveWriter& writer) -> void
		{
			Default::ToArchive(value, writer);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(const T& value, ArchiveWriter& writer)
		{
			Impl(0, value, writer);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'ToArchive' for bool. */
	template <>
	struct CORE_API ToArchive < bool > final
	{
		static void Function(bool value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for char. */
	template <>
	struct CORE_API ToArchive < char > final
	{
		static void Function(char value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for byte. */
	template <>
	struct CORE_API ToArchive < byte > final
	{
		static void Function(byte value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for int16. */
	template <>
	struct CORE_API ToArchive < int16 > final
	{
		static void Function(int16 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for uint16. */
	template <>
	struct CORE_API ToArchive < uint16 > final
	{
		static void Function(uint16 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for int32. */
	template <>
	struct CORE_API ToArchive < int32 > final
	{
		static void Function(int32 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for uint32. */
	template <>
	struct CORE_API ToArchive < uint32 > final
	{
		static void Function(uint32 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for int64. */
	template <>
	struct CORE_API ToArchive < int64 > final
	{
		static void Function(int64 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for uint64. */
	template <>
	struct CORE_API ToArchive < uint64 > final
	{
		static void Function(uint64 value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for float. */
	template <>
	struct CORE_API ToArchive < float > final
	{
		static void Function(float value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for double. */
	template <>
	struct CORE_API ToArchive < double > final
	{
		static void Function(double value, ArchiveWriter& writer);
	};

	/** Implementation of 'ToArchive' for long double. */
	template <>
	struct CORE_API ToArchive < long double > final
	{
		static void Function(long double value, ArchiveWriter& writer);
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'ToArchive' for String. */
	template <>
	struct CORE_API ToArchive < String > final
	{
		static void Function(const String& value, ArchiveWriter& writer);
	};

	///////////////////////////
	///   Container Types   ///

	/** Implementation of 'ToArchive' for Array. */
	template <typename T>
	struct ToArchive < Array<T> > final
	{
		FORCEINLINE static void Function(const Array<T>& array, ArchiveWriter& writer)
		{
			for (const auto& item : array)
			{
				writer.PushValue(item, "item");
			}
		}
	};

	/** Implementation of 'ToArchive' for Queue. */
	template <typename T>
	struct ToArchive < Queue<T> > final
	{
		FORCEINLINE static void Function(const Queue<T>& queue, ArchiveWriter& writer)
		{
			for (const auto& item : queue)
			{
				writer.PushValue(item, "item");
			}
		}
	};

	/** Implementation of 'ToArchive' for Table. */
	template <typename KeyT, typename ValueT>
	struct ToArchive < Table<KeyT, ValueT> > final
	{
		FORCEINLINE static void Function(const Table<KeyT, ValueT>& table, ArchiveWriter& writer)
		{
			for (const auto& pair : table)
			{
				writer.PushHandler(
					[&pair](auto& wr)
					{
						wr.PushValue(pair.First, "key");
						wr.PushValue(pair.Second, "value");
					}, "item");
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Serializes the given value to the given archive. */
template <typename T>
FORCEINLINE void ToArchive(const T& value, ArchiveWriter& writer)
{
	Implementation::ToArchive<T>::Function(value, writer);
}
