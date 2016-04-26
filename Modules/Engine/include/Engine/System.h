// System.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Object.h>
#include "Forwards/Engine.h"
#include "config.h"

namespace willow
{
	class ENGINE_API System : public Object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Object)

		///////////////////
		///   Methods   ///
	public:

		/** Runs the asynchronous update procedure on this System.
		* 'world' - the World that this System is attached to. */
		virtual void update(World& world);
	};
}
