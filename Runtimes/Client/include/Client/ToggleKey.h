// Key.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Window.h"

struct ToggleKey final
{
	////////////////////////
	///   Constructors   ///
public:

	ToggleKey(int key)
		: _key{ key }, _last_result{ GLFW_RELEASE }
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this key has been pressed, compared to the last time 'update' was called. */
	bool update(Window& window)
	{
		const auto result = window.get_key(this->_key);

		if (result != this->_last_result)
		{
			this->_last_result = result;
			return result == GLFW_PRESS;
		}
		else
		{
			return false;
		}
	}

	////////////////
	///   Data   ///
private:

	const int _key;
	int _last_result;
};
