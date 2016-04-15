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
		: First{}, Second{}
	{
		// All done
	}

	template <typename UA, typename UB>
	Pair(UA&& first, UB&& second)
		: First(std::forward<UA>(first)), Second(std::forward<UB>(second))
	{
		// All done
	}

	template <typename PA, typename PB>
	Pair(const Pair<PA, PB>& pair)
		: First(pair.First), Second(pair.Second)
	{
		// All done
	}

	template <typename PA, typename PB>
	Pair(Pair<PA, PB>&& pair)
		: First(std::move(pair.First)), Second(std::move(pair.Second))
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

/** Constructs a pair of the given values. */
template <typename A, typename B>
Pair<std::remove_reference_t<A>, std::remove_reference_t<B>> MakePair(A&& a, B&& b)
{
	return{ std::forward<A>(a), std::forward<B>(b) };
}