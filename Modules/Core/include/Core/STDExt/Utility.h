// Utility.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

namespace stde
{
	/** Returns a reference to the given value as const. */
	template <typename T>
	const T& as_const(const T& value)
	{
		return value;
	}

	/** Not safe for rvalue-references. */
	template <typename T>
	const T& as_const(const T&& value) = delete;
}
