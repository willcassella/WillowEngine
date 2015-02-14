// Pair.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

/** A pair of values */
template <typename A, typename B>
struct Pair final
{
	////////////////////////
	///   Constructors   ///
public:

	/** Default-construct a Pair */
	Pair()
		: First(), Second()
	{
		// All done
	}

	/** Construct a Pair given an instance of the 'A' type */
	Pair(const A& first)
		: First(first), Second()
	{
		// All done
	}

	/** Construct a Pair given an instance of the 'A' type and the 'B' type */
	Pair(const A& first, const B& second)
		: First(first), Second(second)
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