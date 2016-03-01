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
	static void PollEvents();

	/** Returns the current system time. */
	static double GetCurrentTime();
	
	/** Returns whether this Window has mouse and keyboard focus. */
	bool HasFocus() const;

	/** Returns the width of this window. */
	uint32 GetWidth() const;

	/** Returns the height of this Window. */
	uint32 GetHeight() const;

	/** Returns the position of the cursor. */
	Vec2 GetCursorPosition() const;

	/** Centers the cursor on the screen. */
	void CenterCursor();

	/** Returns the state of the given key. */
	int GetKey(int key) const;
	
	/** Returns whether the user is requesting for this Window to close. */
	bool ShouldClose() const;

	/** Swaps the front and back buffers. */
	void SwapBuffers();

	////////////////
	///   Data   ///
private:

	GLFWwindow* _window = nullptr;
};
