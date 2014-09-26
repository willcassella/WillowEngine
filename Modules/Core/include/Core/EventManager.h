// EventManager.h
#pragma once

#include <Utility\String.h>
#include <Utility\Table.h>
#include "InputDispatcher.h"

namespace Willow
{
	// @TODO: Make this a component instead of a member?
	// @TODO: Make it so that there doesn't need to be an instance of this for each class
	class CORE_API EventManager
	{
		////////////////////////
		///   Constructors   ///
	public:

		~EventManager();

		///////////////////
		///   Methods   ///
	public:

		void DispatchInputEvent(const String& eventName, float value);

		// @TODO: add action state (pressed, released, whatever)
		template <class UserClass>
		void BindAction(const String& action, UserClass* object, void(UserClass::*handler)())
		{
			_dispatchers[action].Add(new ActionInputDispatcher<UserClass>(object, handler));
		}

		template <class UserClass>
		void BindAxis(const String& axis, UserClass* object, void(UserClass::*handler)(float))
		{
			_dispatchers[axis].Add(new AxisInputDispatcher<UserClass>(object, handler));
		}

		////////////////
		///   Data   ///
	private:

		Table<String, List<IEventDispatcher*>> _dispatchers;
	};
}