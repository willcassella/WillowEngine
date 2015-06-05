// Pair.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

/** A pair of values */
template <typename FirstType, typename SecondType>
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

	template <typename RelatedFirstType>
	Pair(FirstType&& first)
		: First(std::forward<RelatedFirstType>(first)), Second()
	{
		// All done
	}

	template <typename RelatedFirstType, typename RelatedSecondType>
	Pair(RelatedFirstType&& first, RelatedSecondType&& second)
		: First(std::forward<RelatedFirstType>(first)), Second(std::forward<RelatedSecondType>(second))
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	FirstType First;
	SecondType Second;

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