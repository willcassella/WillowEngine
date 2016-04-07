// System.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Umbrellas/Reflection.h>
#include "../include/Engine/System.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::System);

namespace Willow
{
	///////////////////
	///   Methods   ///

	void System::Update(const World& /*world*/)
	{
		// Do nothing
	}

	void System::PostUpdate(World& /*world*/)
	{
		// Do nothing
	}
}
