// UnMoveable.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

namespace willow
{
	/** Convenient base for types that are not copyable or moveable. */
	struct UnMoveable
	{
		////////////////////////
		///   Constructors   ///
	public:

		UnMoveable() = default;
		UnMoveable(const UnMoveable& copy) = delete;
		UnMoveable(UnMoveable&& move) = delete;

		/////////////////////
		///   Operators   ///
	public:

		UnMoveable& operator=(const UnMoveable& copy) = delete;
		UnMoveable& operator=(UnMoveable&& move) = delete;
	};
}
