// UnCopyable.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

namespace willow
{
	/** Convenient base for any types that do not wish to be copyable. */
	struct UnCopyable
	{
		////////////////////////
		///   Constructors   ///
	public:

		UnCopyable() = default;
		UnCopyable(const UnCopyable& copy) = delete;
		UnCopyable(UnCopyable&& move) = default;

		/////////////////////
		///   Operators   ///
	public:

		UnCopyable& operator=(const UnCopyable& copy) = delete;
		UnCopyable& operator=(UnCopyable&& move) = default;
	};
}
