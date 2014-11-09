// Math.h
#pragma once

#include "..\config.h"

namespace Willow
{
	//////////////////////////
	///   Math Functions   ///
	
	/** Returns the max of two values, with preference to a */
	template <typename T>
	T Max(const T& a, const T& b)
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

	/** Returns the least of two values, with preference to a */
	template <typename T>
	T Min(const T& a, const T& b)
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

	template <typename ValueType, typename RangeType>
	bool InRange(const ValueType& value, const RangeType& lower, const RangeType& upper, bool inclusive = true)
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
}