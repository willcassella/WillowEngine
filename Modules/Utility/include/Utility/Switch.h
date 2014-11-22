// Switch.h
#pragma once

#include "Reflection/Reflection.h"

namespace Willow
{
	/** A class encapsulating a reactive flag */
	class UTILITY_API Switch : public object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		////////////////////////
		///   Constructors   ///
	public:

		Switch(bool value = true);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the new state of the switch */
		bool Toggle();

		/** Returns the state of this switch as a string */
		String ToString() const override;

		/////////////////////
		///   Operators   ///
	public:

		inline operator bool()
		{
			return _value;
		}
		inline Switch& operator=(bool value)
		{
			_value = value;
			return This;
		}

		////////////////
		///   Data   ///
	private:

		bool _value;
	};
}