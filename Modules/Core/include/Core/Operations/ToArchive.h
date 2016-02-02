// ToArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../IO/ArchiveWriter.h"

namespace Operations
{
	/** Generic implementation of 'ToArchive' */
	template <typename T>
	struct ToArchive final
	{
	private:

		/** Detects support for this operation if the 'void ToArchive(ArchiveWriter&) const' member function is present. */
		template <typename F, typename ImplT = decltype(&F::ToArchive)>
		static constexpr bool HasSupport(Implementation::Preferred)
		{
			return std::is_convertible<ImplT, void (F::*)(ArchiveWriter&) const>::value;
		}

		/** Detects lack of support for this operation. */
		template <typename F>
		static constexpr bool HasSupport(Implementation::Fallback)
		{
			return false;
		}

	public:

		/** Executes the operations */
		template <typename F>
		static void Function(const F& value, ArchiveWriter& writer)
		{
			value.ToArchive(writer);
		}

		/** Whether this operation is supported for the given type. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'ToArchive' for bool. */
	template <>
	struct CORE_API ToArchive < bool > final
	{
		static void Function(bool value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for char. */
	template <>
	struct CORE_API ToArchive < char > final
	{
		static void Function(char value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for byte. */
	template <>
	struct CORE_API ToArchive < byte > final
	{
		static void Function(byte value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for int16. */
	template <>
	struct CORE_API ToArchive < int16 > final
	{
		static void Function(int16 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for uint16. */
	template <>
	struct CORE_API ToArchive < uint16 > final
	{
		static void Function(uint16 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for int32. */
	template <>
	struct CORE_API ToArchive < int32 > final
	{
		static void Function(int32 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for uint32. */
	template <>
	struct CORE_API ToArchive < uint32 > final
	{
		static void Function(uint32 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for int64. */
	template <>
	struct CORE_API ToArchive < int64 > final
	{
		static void Function(int64 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for uint64. */
	template <>
	struct CORE_API ToArchive < uint64 > final
	{
		static void Function(uint64 value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for float. */
	template <>
	struct CORE_API ToArchive < float > final
	{
		static void Function(float value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for double. */
	template <>
	struct CORE_API ToArchive < double > final
	{
		static void Function(double value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'ToArchive' for long double. */
	template <>
	struct CORE_API ToArchive < long double > final
	{
		static void Function(long double value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'ToArchive' for String. */
	template <>
	struct CORE_API ToArchive < String > final
	{
		static void Function(const String& value, ArchiveWriter& writer);

		static constexpr bool Supported = true;
	};

	///////////////////////////
	///   Container Types   ///

	/** Implementation of 'ToArchive' for Array. */
	template <typename T>
	struct ToArchive < Array<T> > final
	{
		static void Function(const Array<T>& array, ArchiveWriter& writer)
		{
			for (const auto& item : array)
			{
				writer.PushValue("item", item);
			}
		}

		static constexpr bool Supported = ToArchive<T>::Supported;
	};

	/** Implementation of 'ToArchive' for Stack. */
	template <typename T>
	struct ToArchive < Stack<T> > final
	{
		static void Function(const Stack<T>& stack, ArchiveWriter& writer)
		{
			for (const auto& item : stack)
			{
				writer.PushValue("item", item);
			}
		}

		static constexpr bool Supported = ToArchive<T>::Supported;
	};

	/** Implementation of 'ToArchive' for Queue. */
	template <typename T>
	struct ToArchive < Queue<T> > final
	{
		static void Function(const Queue<T>& queue, ArchiveWriter& writer)
		{
			for (const auto& item : queue)
			{
				writer.PushValue("item", item);
			}
		}

		static constexpr bool Supported = ToArchive<T>::Supported;
	};

	/** Implementation of 'ToArchive' for Table. */
	template <typename KeyT, typename ValueT>
	struct ToArchive < Table<KeyT, ValueT> > final
	{
		static void Function(const Table<KeyT, ValueT>& table, ArchiveWriter& writer)
		{
			for (const auto& pair : table)
			{
				writer.AddChild("item", [&pair](auto& child)
				{
					child.PushValue("key", pair.First);
					child.PushValue("value", pair.Second);
				});
			}
		}

		static constexpr bool Supported = ToArchive<KeyT>::Supported && ToArchive<ValueT>::Supported;
	};
}

/////////////////////
///   Functions   ///

/** Serializes the given value to the given archive. */
template <typename T>
FORCEINLINE void ToArchive(const T& value, ArchiveWriter& writer)
{
	static_assert(Operations::ToArchive<T>::Supported,
		"'ToArchive' is not supported on the given type. If it's supposed to be, make sure the member function signature is correct.");

	Operations::ToArchive<T>::Function(value, writer);
}
