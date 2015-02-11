// IEventDispatcher.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"

class IEventDispatcher : public Interface
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_INTERFACE;

	///////////////////
	///   Methods   ///
public:

	virtual void Dispatch(float value) const = 0;
};