// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <Resource/Archives/XMLArchive.h>
#include <GLRender/GLRenderer.h>
#include "../include/Client/Window.h"

/** Main program loop. */
void EventLoop(Window& window, Willow::World& world, Willow::IRenderer& renderer)
{
	double previous = Window::GetCurrentTime();
	double lastTime = previous;
	double lag = 0.0;
	uint32 numFrames = 0;
	uint32 numUpdates = 0;
	bool shouldExit = false;

	// Begin the event loop
	while (!window.ShouldClose() && !shouldExit)
	{
		double currentTime = Window::GetCurrentTime();
		lag += currentTime - previous;
		previous = currentTime;
		numFrames++;

		if (currentTime - lastTime >= 1.0)
		{
			Console::WriteLine("@ ms/frame = @ fps", 1000.0 / numFrames, numFrames);
			Console::WriteLine("@ updates/second", numUpdates);
			numFrames = 0;
			numUpdates = 0;
			lastTime = currentTime;
		}

		// Poll input events
		Window::PollEvents();

		while (lag >= world.TimeStep)
		{
			Vec2 moveAccum;

			// Check for events
			if (window.GetKey(GLFW_KEY_W))
			{
				moveAccum.Y += 1;
			}
			if (window.GetKey(GLFW_KEY_S))
			{
				moveAccum.Y -= 1;
			}
			if (window.GetKey(GLFW_KEY_D))
			{
				moveAccum.X += 1;
			}
			if (window.GetKey(GLFW_KEY_A))
			{
				moveAccum.X -= 1;
			}
			if (window.GetKey(GLFW_KEY_ESCAPE))
			{
				shouldExit = true;
			}

			// Dispatch events
			world.Events.DispatchEvent("Move", moveAccum.Normalize());
			world.Events.DispatchEvent("Look", window.GetCursorPosition() / 100);
			window.CenterCursor();

			// Update the world
			world.Update();

			lag -= world.TimeStep;
			numUpdates++;
		}

		// Render the frame
		renderer.RenderWorld(world);
		window.SwapBuffers();
	}
}

/** Application entry point. */
int main(int argc, char* argv[])
{
	// Initialize Application
	Application::Initialize();

	// Make sure command line arguments are correct
	if (argc < 3)
	{
		Console::Error("Game module and starting scene not specified. Usage: 'Runtime [game module] [world]'");
		Application::Terminate(EXIT_FAILURE);
	}
	
	// Start up engine
	{
		// Load game module
		Console::WriteLine("Loading module: '@'...", argv[1]);
		Application::LoadModule(argv[1]);

		// Load world
		Console::WriteLine("Loading world: '@'...", argv[2]);
		Willow::World world;
		{
			Willow::XMLArchive archive;
			archive.Load(argv[2]);
			archive.Deserialize(world);
		}

		// Load up subsystems
		Console::WriteLine("Initializing subsystems...");
		Window window("Willow Engine", 1280, 720);
		Willow::GLRenderer renderer(window.GetWidth(), window.GetHeight());

		// Enter main event loop
		Console::WriteLine("Entering event loop...");
		EventLoop(window, world, renderer);
	}
	
	Application::Terminate();
}
