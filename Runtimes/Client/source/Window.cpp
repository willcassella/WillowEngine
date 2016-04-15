// Window.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/Containers/Table.h>
#include <Core/IO/Console.h>
#include <Core/Application.h>
#include "../include/Client/Window.h"

////////////////////////////
///   Static Variables   ///

/** Whether GLFW has been initialized. */
bool GLFWInitialized = false;

/** Table mapping GLFW windows to wrapper Windows, useful for callbacks. */
Table<GLFWwindow*, Window*> WindowTable;

////////////////////////
///   Constructors   ///

Window::Window(CString name, uint32 width, uint32 height)
{
	// Initialize GLFW if this is the first window created
	if (!GLFWInitialized)
	{
		if (!glfwInit())
		{
			Console::Error("GLFW could not be initialized.");
			Application::Terminate(EXIT_FAILURE);
		}
		else
		{
			// Indicate that GLFW has been initialized, and add deinitialize function to run at program exit
			GLFWInitialized = true;
			std::atexit([] { glfwTerminate(); });
		}
	}

	// Get the primary monitor
	auto monitor = glfwGetPrimaryMonitor();
	if (!monitor)
	{
		Console::WriteLine("GLFW failed to get primary monitor.");
		Application::Terminate(EXIT_FAILURE);
	}

	// Get the primary monitor's video mode
	auto videoMode = glfwGetVideoMode(monitor);
	if (!videoMode)
	{
		Console::WriteLine("GLFW failed to get primary monitor video mode.");
		Application::Terminate(EXIT_FAILURE);
	}

	// Set the new window to be invisible
	glfwWindowHint(GLFW_VISIBLE, false);

	// Set the OpenGL context to version 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Create the window
	this->_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (!_window)
	{
		Console::WriteLine("GLFW failed to create window.");
		Application::Terminate(EXIT_FAILURE);
	}

	// Register this window with the window table
	WindowTable[this->_window] = this;

	// Set the window gain/lose focus function
	glfwSetWindowFocusCallback(this->_window, [](GLFWwindow* window, int hasFocus)
	{
		// Reset the cursor position if the window has gained focus
		if (hasFocus)
		{
			WindowTable[window]->center_cursor();
		}
	});

	// Center the window in the screen
	int32 centerX = (videoMode->width - this->get_width()) / 2;
	int32 centerY = (videoMode->height - this->get_height()) / 2;
	glfwSetWindowPos(this->_window, centerX, centerY);

	// Make the window visible
	glfwShowWindow(this->_window);

	// Make the cursor invisible and move it to the center of the window
	glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(this->_window, this->get_width() / 2, this->get_height() / 2);

	// Make an OpenGL context in window
	glfwMakeContextCurrent(this->_window);
}

Window::~Window()
{
	glfwDestroyWindow(this->_window);
	WindowTable.Remove(this->_window);
}

///////////////////
///   Methods   ///

void Window::poll_events()
{
	glfwPollEvents();
}

double Window::get_current_time()
{
	return glfwGetTime();
}

bool Window::has_focus() const
{
	return glfwGetWindowAttrib(this->_window, GLFW_FOCUSED) == 1;
}

uint32 Window::get_width() const
{
	int32 width;
	glfwGetWindowSize(this->_window, &width, nullptr);
	return static_cast<uint32>(width);
}

uint32 Window::get_height() const
{
	int32 height;
	glfwGetWindowSize(this->_window, nullptr, &height);
	return static_cast<uint32>(height);
}

Vec2 Window::get_cursor_position() const
{
	// Make sure the window has focus
	if (!this->has_focus())
	{
		return Vec2::Zero;
	}

	double x;
	double y;
	glfwGetCursorPos(this->_window, &x, &y);

	Vec2 result;
	result.X = static_cast<float>(x) - this->get_width() / 2;
	result.Y = static_cast<float>(y) - this->get_height() / 2;
	return result;
}

void Window::center_cursor()
{
	glfwSetCursorPos(this->_window, this->get_width() / 2, this->get_height() / 2);
}

int Window::get_key(int key) const
{
	return glfwGetKey(this->_window, key);
}

bool Window::should_close() const
{
	return glfwWindowShouldClose(this->_window) != 0;
}

void Window::swap_buffers()
{
	glfwSwapBuffers(this->_window);
}
