// System.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Object.h>
#include "Forwards/Engine.h"
#include "config.h"

namespace Willow
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
		* 'world' - the World that this System is attached to.
		* NOTE: This procedure is run asynchronously among the Systems objects attached to the World.
		* NOTE: This procedure is run prior to the synchronous 'PostUpdate' procedure. */
		virtual void Update(const World& world);

		/** Runs the synchronous post-update procedure on this System. 
		* 'world' - the World that is being updated. 
		* NOTE: This procedure is run synchronously among the System objects attatched to the World.
		* NOTE: This procedure is run after the asynchronous 'Update' procedure. */
		virtual void PostUpdate(World& world);
	};
}
