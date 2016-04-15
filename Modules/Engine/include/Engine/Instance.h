// Instance.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

namespace willow
{
	template <class T>
	struct Instance final
	{
		//////////////////
		///   Fields   ///
	public:

		/** The object refferred to. */
		T* const object;
	};
}
