// SlideComponent.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/Component.h>
#include "config.h"

class EXAMPLEGAME_API SlideComponent : public Component
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Component);

	////////////////////////
	///   Constructors   ///
public:

	SlideComponent(GameObject& owner);

	////////////////////
	///   Handlers   ///
public:

	void OnUpdate(float timeInterval);
};