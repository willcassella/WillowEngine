// FromArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../STDE/TypeTraits.h"
#include "../IO/ArchiveReader.h"
#include "TypeOps.h"

namespace Operations
{
	/** Generic implementation of 'FromArchive'. */
	template <typename T>
	struct FromArchive final
	{
	private:

		/** Detects support for this operation if the 'void FromArchive(const ArchiveReader&)' member function is present. */
		template <typename F, typename ImplT = decltype(&F::FromArchive)>
		static constexpr bool HasSupport(Implementation::Preferred)
		{
			return std::is_convertible<ImplT, void (F::*)(const ArchiveReader&)>::value;
		}

		/** Detects lack of support for this operation. */
		template <typename F>
		static constexpr bool HasSupport(Implementation::Fallback)
		{
			return false;
		}

	public:

		/** Executes the operation. */
		static void Function(T& value, const ArchiveReader& reader)
		{
			value.T::FromArchive(reader);
		}

		/** Whether this operation is supported for the given type. */
		static constexpr bool Supported = HasSupport<T>(0);
	};

	///////////////////////////
	///   Primitive Types   ///

	/** Implementation of 'FromArchive' for bool. */
	template <>
	struct CORE_API FromArchive < bool > final
	{
		static void Function(bool& value, const ArchiveReader& reader);

		static void FailableFunction(bool& value, const ArchiveReader& reader)
		{
			Function(value, reader);
		}

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for char. */
	template <>
	struct CORE_API FromArchive < char > final
	{
		static void Function(char& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for byte. */
	template <>
	struct CORE_API FromArchive < byte > final
	{
		static void Function(byte& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for int16. */
	template <>
	struct CORE_API FromArchive < int16 > final
	{
		static void Function(int16& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for uint16. */
	template <>
	struct CORE_API FromArchive < uint16 > final
	{
		static void Function(uint16& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for int32. */
	template <>
	struct CORE_API FromArchive < int32 > final
	{
		static void Function(int32& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for uint32. */
	template <>
	struct CORE_API FromArchive < uint32 > final
	{
		static void Function(uint32& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for int64. */
	template <>
	struct CORE_API FromArchive < int64 > final
	{
		static void Function(int64& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for uint64. */
	template <>
	struct CORE_API FromArchive < uint64 > final
	{
		static void Function(uint64& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for float. */
	template <>
	struct CORE_API FromArchive < float > final
	{
		static void Function(float& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for double. */
	template <>
	struct CORE_API FromArchive < double > final
	{
		static void Function(double& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	/** Implementation of 'FromArchive' for long double. */
	template <>
	struct CORE_API FromArchive < long double > final
	{
		static void Function(long double& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	////////////////////////
	///   String Types   ///

	/** Implementation of 'FromArchive' for String. */
	template <>
	struct CORE_API FromArchive < String > final
	{
		static void Function(String& value, const ArchiveReader& reader);

		static constexpr bool Supported = true;
	};

	///////////////////////////
	///   Container Types   ///

	/** Implementation of 'FromArchive' for Array. */
	template <typename T>
	struct FromArchive < Array<T> > final
	{
		static void Function(Array<T>& value, const ArchiveReader& reader)
		{
			// Clear the array
			value.Clear();

			// Iterator over 'item' nodes
			reader.EnumerateChildren([&](const auto& itemNode)
			{
				T item;
				::FromArchive(item, itemNode);
				value.Add(std::move(item));
			});
		}

		static constexpr bool Supported = DefaultConstruct<T>::Supported && FromArchive<T>::Supported;
	};

	/** Implementation of 'FromArchive' for Stack. */
	template <typename T>
	struct FromArchive < Stack<T> > final
	{
		static void Function(Stack<T>& stack, const ArchiveReader& reader)
		{
			// Clear the stack
			stack.Clear();

			// Iterate over 'item' nodes
			reader.EnumerateChildren([&stack](const auto& itemNode)
			{
				T item;
				::FromArchive(item, itemNode);
				stack.Push(std::move(item));
			});
		}

		static constexpr bool Supported = DefaultConstruct<T>::Supported && FromArchive<T>::Supported;
	};

	/** Implementation of 'FromArchive' for Queue. */
	template <typename T>
	struct FromArchive < Queue<T> > final
	{
		static void Function(Queue<T>& queue, const ArchiveReader& reader)
		{
			// Clear the queue
			queue.Clear();

			// Iterate over 'item' nodes
			reader.EnumerateChildren([&](const auto& itemNode)
			{
				T item;
				::FromArchive(item, itemNode);
				queue.Push(std::move(item));
			});
		}

		static constexpr bool Supported = DefaultConstruct<T>::Supported && FromArchive<T>::Supported;
	};

	/** Implementation of 'FromArchive' for Table. */
	template <typename KeyT, typename ValueT>
	struct FromArchive < Table<KeyT, ValueT> > final
	{
		static void Function(Table<KeyT, ValueT>& table, const ArchiveReader& reader)
		{
			// Reset the table
			table.Clear();

			// Enumerate over 'item' nodes
			reader.EnumerateChildren([&](const auto& item)
			{
				KeyT key;
				bool loadedKey = false;
				ValueT value;
				bool loadedValue = false;

				// Deserialize the key
				loadedKey = item.GetChild("key", [&](const auto& child)
				{
					::FromArchive(key, child);
				});

				// Deserialize the value
				loadedValue = item.GetChild("value", [&](const auto& child)
				{
					::FromArchive(value, child);
				});

				// If both were loaded, add value to table
				if (loadedKey && loadedValue)
				{
					table.Insert(std::move(key), std::move(value));
				}
			});
		}

		static constexpr bool Supported = 
			DefaultConstruct<KeyT>::Supported && 
			DefaultConstruct<ValueT>::Supported && 
			FromArchive<KeyT>::Supported &&
			FromArchive<ValueT>::Supported;
	};
}

/////////////////////
///   Functions   ///

/** TODO: Documentation */
template <typename T>
FORCEINLINE void FromArchive(T& value, const ArchiveReader& reader)
{
	static_assert(Operations::FromArchive<T>::Supported,
		"'FromArchive' is not supported on the given type. If it's supposed to be, make sure the member function signature is correct.");

	Operations::FromArchive<T>::Function(value, reader);
}
