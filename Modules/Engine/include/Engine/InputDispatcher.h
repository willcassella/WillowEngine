// InputDispatcher.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "IEventDispatcher.h"

/** Dispatcher for action based input */
template <class UserClass>
class ActionInputDispatcher : public Object, IEventDispatcher
{
	////////////////////////
	///   Constructors   ///
public:

	ActionInputDispatcher(UserClass* object, void(UserClass::*handler)())
	{
		_object = object;
		_handler = handler;
	}
	~ActionInputDispatcher() override = default;

	///////////////////
	///   Methods   ///
public:

	void Dispatch(float value) const override
	{
		// Ignore value
		(_object->*_handler)();
	}

	////////////////
	///   Data   ///
private:

	UserClass* _object;
	void(UserClass::*_handler)();
};

// Dispatcher for axis based input
template <class UserClass>
class AxisInputDispatcher : public IEventDispatcher
{
	////////////////////////
	///   Constructors   ///
public:

	AxisInputDispatcher(UserClass* object, void(UserClass::*handler)(float))
	{
		_object = object;
		_handler = handler;
	}
	~AxisInputDispatcher() override = default;

	///////////////////
	///   Methods   ///
public:

	void Dispatch(float value) const override
	{
		(_object->*_handler)(value);
	}

	////////////////
	///   Data   ///
private:

	UserClass* _object;
	void(UserClass::*_handler)(float);
};