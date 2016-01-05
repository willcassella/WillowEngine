// Pair.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"
#include "../STDExt/TypeTraits.h"

/** A pair of values */
template <typename A, typename B>
struct Pair final
{
	////////////////////////
	///   Constructors   ///
public:

	Pair()
		: First(), Second()
	{
		// All done
	}

	template <typename RelA, WHERE(std::is_constructible<A, RelA>::value)>
	Pair(RelA&& first)
		: First(std::forward<RelA>(first)), Second()
	{
		// All done
	}

	template <typename RelA, typename RelB, WHERE(std::is_constructible<A, RelA>::value && std::is_constructible<B, RelB>::value)>
	Pair(RelA&& first, RelB&& second)
		: First(std::forward<RelA>(first)), Second(std::forward<RelB>(second))
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	A First;
	B Second;

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const Pair& lhs, const Pair& rhs)
	{
		return lhs.First == rhs.First && lhs.Second == rhs.Second;
	}
	friend FORCEINLINE bool operator!=(const Pair& lhs, const Pair& rhs)
	{
		return lhs.First != rhs.First || lhs.Second != rhs.Second;
	}
};