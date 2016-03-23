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

		////////////////////////
		///   Constructors   ///
	public:

		System(World& world);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the World that this System is attached to. */
		FORCEINLINE World& GetWorld()
		{
			return *_world;
		}

		/** Returns the World that this System is attached to. */
		FORCEINLINE const World& GetWorld() const
		{
			return *_world;
		}

		/** Runs update procedure on this System. */
		virtual void Update();

		/** Runs post-update procedure on this System. */
		virtual void PostUpdate();

		////////////////
		///   Data   ///
	public:

		World* _world;
	};
}
