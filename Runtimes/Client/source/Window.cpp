// Window.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <Core/Application.h>
#include "../include/Client/Window.h"

////////////////////////
///   Constructors   ///

Window::Window(CString name, uint32 width, uint32 height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		Console::WriteLine("GLFW Initialization failure");
		Application::Terminate(EXIT_FAILURE);
	}

	// Get the primary monitor
	auto monitor = glfwGetPrimaryMonitor();
	if (!monitor)
	{
		Console::WriteLine("GLFW failed to get primary monitor.");
		glfwTerminate();
		Application::Terminate(EXIT_FAILURE);
	}

	// Get the primary monitor's video mode
	auto videoMode = glfwGetVideoMode(monitor);
	if (!videoMode)
	{
		Console::WriteLine("GLFW failed to get primary monitor video mode.");
		glfwTerminate();
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
		glfwTerminate();
		Application::Terminate(EXIT_FAILURE);
	}

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
	glfwTerminate();
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
