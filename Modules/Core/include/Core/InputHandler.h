// InputHandler.h
#pragma once

#include <Utility\String.h>
#include <Utility\AssociativeArray.h>
#include <Utility\Array.h>
#include "InputDispatcher.h"

namespace Willow
{
	template class CORE_API AssociativeArray<String, Array<IInputDispatcher*>>;

	// @TODO: Make this a component instead of a member?
	class CORE_API InputHandler
	{
		////////////////////////
		///   Constructors   ///
	public:

		~InputHandler();

		///////////////////
		///   Methods   ///
	public:

		void DispatchInput(const String& eventName, float value)
		{
			if (_dispatchers.HasKey(eventName))
			{
				Array<IInputDispatcher*>& handlers = _dispatchers[eventName];
				for (uint32 i = 0; i < handlers.Size(); i++)
				{
					handlers[i]->Dispatch(value);
				}
			}
		}

		// @TODO: add action state (pressed, released, whatever)
		template <class UserClass>
		void BindAction(const String& action, UserClass* object, void(UserClass::*handler)())
		{
			if (!_dispatchers.HasKey(action))
			{
				_dispatchers[action] = Array<IInputDispatcher*>();
			}

			_dispatchers[action].Add(new ActionDispatcher<UserClass>(object, handler));
		}

		template <class UserClass>
		void BindAxis(const String& axis, UserClass* object, void(UserClass::*handler)(float))
		{
			if (!_dispatchers.HasKey(axis))
			{
				_dispatchers[axis] = Array<IInputDispatcher*>();
			}

			_dispatchers[axis].Add(new AxisDispatcher<UserClass>(object, handler));
		}

		////////////////
		///   Data   ///
	private:

		AssociativeArray<String, Array<IInputDispatcher*>> _dispatchers;
	};
}