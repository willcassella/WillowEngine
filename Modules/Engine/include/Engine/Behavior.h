// Behavior.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Forwards/Engine.h"

class ENGINE_API Behavior : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(Object)

	////////////////////////
	///   Constructors   ///
public:

	Behavior();

	///////////////////
	///   Methods   ///
public:

	FORCEINLINE GameObject& GetOwner()
	{
		return *_owner;
	}

	FORCEINLINE const GameObject& GetOwner() const
	{
		return *_owner;
	}

	////////////////
	///   Data   ///
private:

	GameObject* _owner;
};
