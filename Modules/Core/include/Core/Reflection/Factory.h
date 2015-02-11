// Factory.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** Code used for generating type factories */
#pragma once

#include "Value.h"
#include "Reference.h"
#include "PointerInfo.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Default implementation of factory construction on stack */
	template <typename AnyType>
	struct StackFactory
	{
		inline static Value Function()
		{
			return AnyType();
		}
	};

	/** Default implementation of factory construction on heap */
	template <typename AnyType>
	struct HeapFactory
	{
		inline static Reference Function()
		{
			return *new AnyType();
		}
	};

	/** Stack factory construction for boolean */
	template <>
	struct StackFactory < bool >
	{
		inline static Value Function()
		{
			return bool(false);
		}
	};

	/** Heap factory construction for boolean */
	template <>
	struct HeapFactory < bool >
	{
		inline static Reference Function()
		{
			return *new bool(false);
		}
	};

	/** Stack factory construction for character */
	template <>
	struct StackFactory < char >
	{
		inline static Value Function()
		{
			return char('\0');
		}
	};

	/** Heap factory construction for character */
	template <>
	struct HeapFactory < char >
	{
		inline static Reference Function()
		{
			return *new char('\0');
		}
	};

	/** Stack factory construction for byte */
	template <>
	struct StackFactory < byte >
	{
		inline static Value Function()
		{
			return byte(0);
		}
	};

	/** Heap factory construction for byte */
	template<>
	struct HeapFactory < byte >
	{
		inline static Reference Function()
		{
			return *new byte(0);
		}
	};

	/** Stack factory construction for 16-bit integer */
	template <>
	struct StackFactory < int16 >
	{
		inline static Value Function()
		{
			return int16(0);
		}
	};

	/** Heap factory construction for 16-bit integer */
	template <>
	struct HeapFactory < int16 >
	{
		inline static Reference Function()
		{
			return *new int16(0);
		}
	};

	/** Stack factory construction for 32-bit integer */
	template <>
	struct StackFactory < int32 >
	{
		inline static Value Function()
		{
			return int32(0);
		}
	};

	/** Heap factory construction for 32-bit integer */
	template <>
	struct HeapFactory < int32 >
	{
		inline static Reference Function()
		{
			return *new int32(0);
		}
	};

	/** Stack factory construction for 64-bit integer */
	template <>
	struct StackFactory < int64 >
	{
		inline static Value Function()
		{
			return int64(0);
		}
	};

	/** Heap factory construction for 64-bit integer */
	template <>
	struct HeapFactory < int64 >
	{
		inline static Reference Function()
		{
			return *new int64(0);
		}
	};

	/** Stack factory construction for 16-bit unsigned integer */
	template <>
	struct StackFactory < uint16 >
	{
		inline static Value Function()
		{
			return uint16(0);
		}
	};

	/** Heap factory construction for 16-bit unsigned integer */
	template <>
	struct HeapFactory < uint16 >
	{
		inline static Reference Function()
		{
			return *new uint16(0);
		}
	};

	/** Stack factory construction for 32-bit unsigned integer */
	template <>
	struct StackFactory < uint32 >
	{
		inline static Value Function()
		{
			return int32(0);
		}
	};

	/** Heap factory construction for 32-bit unsigned integer */
	template <>
	struct HeapFactory < uint32 >
	{
		inline static Reference Function()
		{
			return *new uint32(0);
		}
	};

	/** Stack factory construction for 64-bit unsigned integer */
	template <>
	struct StackFactory < uint64 >
	{
		inline static Value Function()
		{
			return uint64(0);
		}
	};

	/** Heap factory construction for 64-bit unsigned integer */
	template <>
	struct HeapFactory < uint64 >
	{
		inline static Reference Function()
		{
			return *new uint64(0);
		}
	};

	/** Stack factory construction for float */
	template <>
	struct StackFactory < float >
	{
		inline static Value Function()
		{
			return float(0);
		}
	};

	/** Heap factory construction for float */
	template <>
	struct HeapFactory < float >
	{
		inline static Reference Function()
		{
			return *new float(0);
		}
	};

	/** Stack factory construction for double */
	template <>
	struct StackFactory < double >
	{
		inline static Value Function()
		{
			return double(0);
		}
	};

	/** Heap factory construction for double */
	template <>
	struct HeapFactory < double >
	{
		inline static Reference Function()
		{
			return *new double(0);
		}
	};

	/** Stack factory construction for pointers */
	template <typename AnyType>
	struct StackFactory < AnyType* >
	{
		inline static Value Function()
		{
			// Fuck you, error C2275
			AnyType* value = nullptr;
			return value;
		}
	};

	/** Heap factory construction for pointers */
	template <typename AnyType>
	struct HeapFactory < AnyType* >
	{
		inline static Reference Function()
		{
			return *new AnyType*(nullptr);
		}
	};
}

/////////////////////
///   Functions   ///

/** Returns a stack-allocated instance of the given type 
* DO NOT OVERLOAD: Specialize struct 'Implementation::StackInstance' */
template <typename AnyType>
Value StackFactory()
{
	return Implementation::StackFactory<AnyType>::Function();
}

/** Returns a heap-allocated instance of the given type
* NOTE: Callee has ownership over the lifetime of returned value (it must be deleted manually) 
* DO NOT OVERLOAD: Specialize struct 'Implementation::HeapInstance' */
template <typename AnyType>
Reference HeapFactory()
{
	return Implementation::HeapFactory<AnyType>::Function();
}