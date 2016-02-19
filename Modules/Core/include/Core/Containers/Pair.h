// Pair.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <utility>
#include "../env.h"

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

	template <typename UA>
	Pair(UA&& first)
		: First(std::forward<UA>(first)), Second()
	{
		// All done
	}

	template <typename UA, typename UB>
	Pair(UA&& first, UB&& second)
		: First(std::forward<UA>(first)), Second(std::forward<UB>(second))
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