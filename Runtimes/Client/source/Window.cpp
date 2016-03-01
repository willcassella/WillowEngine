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
	_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	if (!_window)
	{
		Console::WriteLine("GLFW failed to create window.");
		Application::Terminate(EXIT_FAILURE);
	}

	// Register this window with the window table
	WindowTable[_window] = this;

	// Set the window gain/lose focus function
	glfwSetWindowFocusCallback(_window, [](GLFWwindow* window, int hasFocus)
	{
		// Reset the cursor position if the window has gained focus
		if (hasFocus == GLFW_TRUE)
		{
			WindowTable[window]->CenterCursor();
		}
	});

	// Center the window in the screen
	int32 centerX = (videoMode->width - this->GetWidth()) / 2;
	int32 centerY = (videoMode->height - this->GetHeight()) / 2;
	glfwSetWindowPos(_window, centerX, centerY);

	// Make the window visible
	glfwShowWindow(_window);

	// Make the cursor invisible and move it to the center of the window
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(_window, this->GetWidth() / 2, this->GetHeight() / 2);

	// Make an OpenGL context in window
	glfwMakeContextCurrent(_window);
}

Window::~Window()
{
	glfwDestroyWindow(_window);
	WindowTable.Remove(_window);
}

///////////////////
///   Methods   ///

void Window::PollEvents()
{
	glfwPollEvents();
}

double Window::GetCurrentTime()
{
	return glfwGetTime();
}

bool Window::HasFocus() const
{
	return glfwGetWindowAttrib(_window, GLFW_FOCUSED) == GLFW_TRUE;
}

uint32 Window::GetWidth() const
{
	int32 width;
	glfwGetWindowSize(_window, &width, nullptr);
	return static_cast<uint32>(width);
}

uint32 Window::GetHeight() const
{
	int32 height;
	glfwGetWindowSize(_window, nullptr, &height);
	return static_cast<uint32>(height);
}

Vec2 Window::GetCursorPosition() const
{
	// Make sure the window has focus
	if (!this->HasFocus())
	{
		return Vec2::Zero;
	}

	double x;
	double y;
	glfwGetCursorPos(_window, &x, &y);

	Vec2 result;
	result.X = static_cast<float>(x) - this->GetWidth() / 2;
	result.Y = static_cast<float>(y) - this->GetHeight() / 2;
	return result;
}

void Window::CenterCursor()
{
	glfwSetCursorPos(_window, this->GetWidth() / 2, this->GetHeight() / 2);
}

int Window::GetKey(int key) const
{
	return glfwGetKey(_window, key);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(_window) != 0;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(_window);
}
