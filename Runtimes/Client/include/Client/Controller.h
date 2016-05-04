// Controller.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <GLFW/glfw3.h>
#include <Core/Math/Vec2.h>

struct Controller final
{
	////////////////////////
	///   Constructors   ///
public:

	Controller(int index, float deadZone)
		: _index{ index }, _dead_zone{ deadZone }
	{
		_jump_last_state = GLFW_RELEASE;
	}

	///////////////////
	///   Methods   ///
public:

	int get_index() const
	{
		return _index + 1;
	}

	Vec2 get_lstick() const
	{
		Vec2 result;
		int count;
		auto axes = glfwGetJoystickAxes(_index, &count);

		if (count >= 1)
		{
			result.X = get_with_deadzone(axes[0]);
			result.Y = get_with_deadzone(-axes[1]);
		}

		return result;
	}

	Vec2 get_rstick() const
	{
		Vec2 result;
		int count;
		auto axes = glfwGetJoystickAxes(_index, &count);

		if (count >= 4)
		{
			result.X = get_with_deadzone(axes[4]);
			result.Y = get_with_deadzone(axes[3]);
		}
		
		return result;
	}

	bool get_jump() const
	{
		int count;
		auto* buttons = glfwGetJoystickButtons(_index, &count);

		if (_jump_last_state != buttons[0])
		{
			_jump_last_state = buttons[0];
			return _jump_last_state == GLFW_PRESS;
		}
		else
		{
			return false;
		}
	}

	bool get_fire() const
	{
		int count;
		auto axes = glfwGetJoystickAxes(_index, &count);

		bool pressed = axes[2] <= -_dead_zone;
		
		if (_fire_last_state != pressed)
		{
			_fire_last_state = pressed;
			return pressed;
		}
		else
		{
			return false;
		}
	}

private:

	float get_with_deadzone(float axis) const
	{
		if (axis > _dead_zone || axis < -_dead_zone)
		{
			return axis;
		}
		else
		{
			return 0;
		}
	}

	////////////////
	///   Data   ///
private:

	const int _index;
	const float _dead_zone;
	mutable char _jump_last_state;
	mutable bool _fire_last_state;
};
