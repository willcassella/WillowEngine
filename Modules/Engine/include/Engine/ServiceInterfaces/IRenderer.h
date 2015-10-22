// IRenderer.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../config.h"

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'Scene.h' */
class Scene;

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

	virtual void RenderScene(const Scene& scene) = 0;
};
