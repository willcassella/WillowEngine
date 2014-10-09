// Switch.h
#pragma once

#include "config.h"

namespace Willow
{
	/** A class encapsulating a reactive flag */
	class UTILITY_API Switch
	{
		////////////////////////
		///   Constructors   ///
	public:

		Switch(bool value = true);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the new state of the switch */
		bool Toggle();

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