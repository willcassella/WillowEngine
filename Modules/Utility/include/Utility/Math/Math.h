// Math.h
#pragma once

#include "..\config.h"

namespace Willow
{
	//////////////////////////
	///   Math Functions   ///

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
}