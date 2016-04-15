// Window.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <GLFW/glfw3.h>
#include <Core/Math/Vec2.h>

/** Class representing a GLFW window. Heavily designed towards the uses of "Client",
* not meant to be a general-purpose abstraction over GLFW. */
struct Window final
{
	////////////////////////
	///   Constructors   ///
public:

	Window(CString name, uint32 width, uint32 height);
	Window(const Window& copy) = delete;
	Window(Window&& move) = delete;
	~Window();

	///////////////////
	///   Methods   ///
public:

	/** Polls for GLFW events. */
	static void poll_events();

	/** Returns the current system time. */
	static double get_current_time();
	
	/** Returns whether this Window has mouse and keyboard focus. */
	bool has_focus() const;

	/** Returns the width of this window. */
	uint32 get_width() const;

	/** Returns the height of this Window. */
	uint32 get_height() const;

	/** Returns the position of the cursor. */
	Vec2 get_cursor_position() const;

	/** Centers the cursor on the screen. */
	void center_cursor();

	/** Returns the state of the given key. */
	int get_key(int key) const;
	
	/** Returns whether the user is requesting for this Window to close. */
	bool should_close() const;

	/** Swaps the front and back buffers. */
	void swap_buffers();

	////////////////
	///   Data   ///
private:

	GLFWwindow* _window = nullptr;
};
