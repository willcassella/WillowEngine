// IRenderer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'World.h' */
class World;

/////////////////
///   Types   ///

class ENGINE_API IRenderer
{
	////////////////////////
	///   Constructors   ///
public:

	virtual ~IRenderer() = default;

	///////////////////
	///   Methods   ///
public:

	virtual void RenderWorld(const World& world) = 0;
};
