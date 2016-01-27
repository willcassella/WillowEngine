// ToArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../IO/OutArchive.h"

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
		FORCEINLINE static auto Impl(Preferred, const F& value, OutArchive& archive) -> decltype(value.F::ToArchive(archive))
		{
			return value.ToArchive(archive);
		}

		/** Implementation for types that do not defined their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, const F& value, OutArchive& archive) -> void
		{
			Default::ToArchive(value, archive);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(const T& value, OutArchive& archive)
		{
			Impl(0, value, archive);
		}
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'ToArchive' for bool. */
	template <>
	struct CORE_API ToArchive < bool > final
	{
		static void Function(bool value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for char. */
	template <>
	struct CORE_API ToArchive < char > final
	{
		static void Function(char value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for byte. */
	template <>
	struct CORE_API ToArchive < byte > final
	{
		static void Function(byte value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for int16. */
	template <>
	struct CORE_API ToArchive < int16 > final
	{
		static void Function(int16 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for uint16. */
	template <>
	struct CORE_API ToArchive < uint16 > final
	{
		static void Function(uint16 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for int32. */
	template <>
	struct CORE_API ToArchive < int32 > final
	{
		static void Function(int32 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for uint32. */
	template <>
	struct CORE_API ToArchive < uint32 > final
	{
		static void Function(uint32 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for int64. */
	template <>
	struct CORE_API ToArchive < int64 > final
	{
		static void Function(int64 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for uint64. */
	template <>
	struct CORE_API ToArchive < uint64 > final
	{
		static void Function(uint64 value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for float. */
	template <>
	struct CORE_API ToArchive < float > final
	{
		static void Function(float value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for double. */
	template <>
	struct CORE_API ToArchive < double > final
	{
		static void Function(double value, OutArchive& archive);
	};

	/** Implementation of 'ToArchive' for long double. */
	template <>
	struct CORE_API ToArchive < long double > final
	{
		static void Function(long double value, OutArchive& archive);
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'ToArchive' for String. */
	template <>
	struct CORE_API ToArchive < String > final
	{
		static void Function(const String& value, OutArchive& archive);
	};

	///////////////////////////
	///   Container Types   ///

	/** Implementation of 'ToArchive' for Array. */
	template <typename T>
	struct ToArchive < Array<T> > final
	{
		FORCEINLINE static void Function(const Array<T>& array, OutArchive& archive)
		{
			for (const auto& item : array)
			{
				archive.Push(item, "item");
			}
		}
	};

	/** Implementation of 'ToArchive' for Queue. */
	template <typename T>
	struct ToArchive < Queue<T> > final
	{
		FORCEINLINE static void Function(const Queue<T>& queue, OutArchive& archive)
		{
			for (const auto& item : queue)
			{
				archive.Push(item, "item");
			}
		}
	};

	/** Implementation of 'ToArchive' for Table. */
	template <typename KeyT, typename ValueT>
	struct ToArchive < Table<KeyT, ValueT> > final
	{
		FORCEINLINE static void Function(const Table<KeyT, ValueT>& table, OutArchive& archive)
		{
			for (const auto& pair : table)
			{
				archive.PushHandler(
					[&pair](auto& ar)
					{
						ar.Push(pair.First, "key");
						ar.Push(pair.Second, "value");
					}, "item");
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Serializes the given value to the given archive. */
template <typename T>
FORCEINLINE void ToArchive(const T& value, OutArchive& archive)
{
	Implementation::ToArchive<T>::Function(value, archive);
}
