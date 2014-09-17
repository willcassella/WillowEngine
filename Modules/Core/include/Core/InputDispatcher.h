// InputDispatcher.h
#pragma once

#include "config.h"

namespace Willow
{
	interface IInputDispatcher
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~IInputDispatcher()
		{
			// Do nothing
		}

		///////////////////
		///   Methods   ///
	public:

		virtual void Dispatch(float value) const = 0;
	};

	// Dispatcher for action based input
	template <class UserClass>
	class ActionDispatcher : public IInputDispatcher
	{
		////////////////////////
		///   Constructors   ///
	public:

		ActionDispatcher(UserClass* object, void(UserClass::*handler)())
		{
			_object = object;
			_handler = handler;
		}
		~ActionDispatcher() override
		{
			// Do nothing
		}

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
	class AxisDispatcher : public IInputDispatcher
	{
		////////////////////////
		///   Constructors   ///
	public:

		AxisDispatcher(UserClass* object, void(UserClass::*handler)(float))
		{
			_object = object;
			_handler = handler;
		}
		~AxisDispatcher() override
		{
			// Do nothing
		}

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
}