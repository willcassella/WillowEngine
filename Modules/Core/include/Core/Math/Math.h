// Math.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

/////////////////////
///   Functions   ///
	
/** Returns the greater of two values, with preference to 'a' */
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

/** Returns the given value, clamped between the given upper and lower bounds */
template <typename T>
FORCEINLINE T Clamp(const T& value, const T& lowerBound, const T& upperBound)
{
	return Min(Max(value, lowerBound), upperBound);
}

/** Returns whether the given value is between the given bounds */
template <typename T>
bool InRange(const T& value, const T& lowerBound, const T& upperBound, bool lowerInclusive = true, bool upperInclusive = true)
{
	bool aboveLower;
	bool belowUpper;

	if (lowerInclusive)
	{
		aboveLower = value >= lowerBound;
	}
	else
	{
		aboveLower = value > lowerBound;
	}

	if (upperInclusive)
	{
		belowUpper = value <= upperBound;
	}
	else
	{
		belowUpper = value < upperBound;
	}

	return aboveLower && belowUpper;
}