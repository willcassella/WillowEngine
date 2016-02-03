// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <GLRender/GLRenderer.h>
#include <ExampleGame/FPSCharacter.h>
#include "../include/Client/Window.h"

/** Main program loop. */
void EventLoop(Window& window, World& world, IRenderer& renderer)
{
	Console::WriteLine("Entering event loop...");

	double previous = glfwGetTime();
	double lastTime = previous;
	double lag = 0.0;
	uint32 numFrames = 0;
	uint32 numUpdates = 0;
	bool shouldExit = false;

	// Begin the event loop
	while (!window.ShouldClose() && !shouldExit)
	{
		double currentTime = glfwGetTime();
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

		// Free memory
		Application::GetMemoryManager().Sweep();
	}

	Console::WriteLine("Leaving event loop...");
}

/** Application entry point. */
int main(int32 /*argc*/, char** /*argv*/)
{
	// Initialize Application
	Application::Initialize();

	// Create a window, the renderer, and world to simulate
	{
		Console::WriteLine("Initializing subsystems...");
		Window window("Willow Engine", 1280, 720);
		GLRenderer renderer(window.GetWidth(), window.GetHeight());

		///////////////////////////////
		///   Setting up a simple   ///
		///          scene          ///

		Console::WriteLine("Creating world...");

		UniquePtr<World> world = New<World>();

		auto& sponza = world->Spawn<StaticMeshComponent>("Sponza");
		sponza.SetScale({ 0.6f, 0.6f, 0.6f });
		sponza.Mesh = "Content/Models/sponza_new.wmesh"_p;
		sponza.Material = "Content/Materials/Sponza.mat"_p;
		sponza.InstanceParams["diffuse"] = AssetPtr<Texture>("Content/Textures/sponza_new_tex.png"_p);

		auto& player = world->Spawn<FPSCharacter>("Player");
		player.Translate({ 0, 3, 0 });

		// Enter main event loop
		EventLoop(window, *world, renderer);
	}
	
	Application::Terminate();
}
