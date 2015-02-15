// Math.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

/////////////////////
///   Functions   ///
	
/** Returns the max of two values, with preference to 'a' */
template <typename T>
FORCEINLINE const T& Max(const T& a, const T& b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

/** Returns the least of two values, with preference to 'a' */
template <typename T>
FORCEINLINE const T& Min(const T& a, const T& b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

// @TODO: Documentation
template <typename T>
bool InRange(const T& value, const T& lower, const T& upper, bool inclusive = true)
{
	if (inclusive)
	{
		return value >= lower && value <= upper;
	}
	else
	{
		return value > lower && value < upper;
	}
}

// @TODO: sin, cosine, sqrt, tan, etc