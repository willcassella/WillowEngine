// Tuple.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

/** Tuple of 3 to five different values
* If you need more than five, just use an Array or something (or create your own damn struct) */
template <typename ... AnyTypes>
struct Tuple;

/** Tuple of three elements */
template <typename FirstType, typename SecondType, typename ThirdType>
struct Tuple < FirstType, SecondType, ThirdType > final
{
	////////////////////////
	///   Constructors   ///
public:

	Tuple()
		: First(), Second(), Third()
	{
		// All done
	}
	Tuple(const FirstType& first)
		: First(first), Second(), Third()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second)
		: First(first), Second(second), Third()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third)
		: First(first), Second(second), Third(third)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	FirstType First;
	SecondType Second;
	ThirdType Third;

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First == rhs.First && lhs.Second == rhs.Second && lhs.Third == rhs.Third;
	}
	friend FORCEINLINE bool operator!=(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First != rhs.First || lhs.Second != rhs.Second || lhs.Third != rhs.Third;
	}
};

/** Tuple of four elements */
template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType>
struct Tuple < FirstType, SecondType, ThirdType, FourthType > final
{
	////////////////////////
	///   Constructors   ///
public:

	Tuple()
		: First(), Second(), Third(), Fourth()
	{
		// All done
	}
	Tuple(const FirstType& first)
		: First(first), Second(), Third(), Fourth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second)
		: First(first), Second(second), Third(), Fourth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third)
		: First(first), Second(second), Third(third), Fourth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third, const FourthType& fourth)
		: First(first), Second(second), Third(third), Fourth(fourth)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	FirstType First;
	SecondType Second;
	ThirdType Third;
	FourthType Fourth;

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First == rhs.First && lhs.Second == rhs.Second && lhs.Third == rhs.Third && lhs.Fourth == rhs.Fourth;
	}
	friend FORCEINLINE bool operator!=(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First != rhs.First || lhs.Second != rhs.Second || lhs.Third != rhs.Third || lhs.Fourth != rhs.Fourth;
	}
};

/** Tuple of five elements */
template <typename FirstType, typename SecondType, typename ThirdType, typename FourthType, typename FifthType>
struct Tuple < FirstType, SecondType, ThirdType, FourthType, FifthType > final
{
	////////////////////////
	///   Constructors   ///
public:

	Tuple()
		: First(), Second(), Third(), Fourth(), Fifth()
	{
		// All done
	}
	Tuple(const FirstType& first)
		: First(first), Second(), Third(), Fourth(), Fifth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second)
		: First(first), Second(second), Third(), Fourth(), Fifth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third)
		: First(first), Second(second), Third(third), Fourth(), Fifth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third, const FourthType& fourth)
		: First(first), Second(second), Third(third), Fourth(fourth), Fifth()
	{
		// All done
	}
	Tuple(const FirstType& first, const SecondType& second, const ThirdType& third, const FourthType& fourth, const FifthType& fifth)
		: First(first), Second(second), Third(third), Fourth(fourth), Fifth(fifth)
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	FirstType First;
	SecondType Second;
	ThirdType Third;
	FourthType Fourth;
	FifthType Fifth;

	/////////////////////
	///   Operators   ///
public:

	friend FORCEINLINE bool operator==(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First == rhs.First && lhs.Second == rhs.Second && lhs.Third == rhs.Third && lhs.Fourth == rhs.Fourth && lhs.Fifth == rhs.Fifth;
	}
	friend FORCEINLINE bool operator!=(const Tuple& lhs, const Tuple& rhs)
	{
		return lhs.First != lhs.First || lhs.Second != rhs.Second || lhs.Third != rhs.Third || lhs.Fourth != rhs.Fourth || lhs.Fifth != rhs.Fifth;
	}
};