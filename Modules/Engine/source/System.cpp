// System.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/System.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::System);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	System::System(World& world)
		: _world(&world)
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void System::Update()
	{
		// Do nothing
	}

	void System::PostUpdate()
	{
		// Do nothing
	}
}
