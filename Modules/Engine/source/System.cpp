// System.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/System.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::System);

namespace willow
{
	///////////////////
	///   Methods   ///

	void System::update(const World& /*world*/)
	{
		// Do nothing
	}

	void System::post_update(World& /*world*/)
	{
		// Do nothing
	}
}
