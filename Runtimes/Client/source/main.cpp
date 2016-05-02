// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <Resource/Archives/XMLArchive.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Systems/AnimationSystem.h>
#include <BulletPhysics/BulletPhysicsSystem.h>
#include <GLRender/GLRenderSystem.h>
#include "../include/Client/Window.h"
#include "../include/Client/ToggleKey.h"
#include "../include/Client/Controller.h"

/** Main program loop. */
void event_loop(Window& window, willow::World& world, willow::RenderSystem& renderer, willow::PhysicsSystem& physics)
{
	double previous = Window::get_current_time();
	double lastTime = previous;
	double lag = 0.0;
	uint32 numFrames = 0;
	uint32 numUpdates = 0;
	bool shouldExit = false;
	bool drawPhysics = false;
	ToggleKey drawPhysicsKey{ GLFW_KEY_F1 };
	Controller controller{ GLFW_JOYSTICK_1, 0.2f };

	// Begin the event loop
	while (!window.should_close() && !shouldExit)
	{
		double currentTime = Window::get_current_time();
		lag += currentTime - previous;
		previous = currentTime;
		numFrames++;

		if (currentTime - lastTime >= 1.0)
		{
			Console::WriteLine("@ ms/frame = @ fps", 1000.0 / numFrames, numFrames);
			Console::WriteLine("@ updates/second", numUpdates);
			Console::WriteLine("Drawing @ static meshes", world.enumerate_objects<willow::StaticMeshComponent>().Size());
			numFrames = 0;
			numUpdates = 0;
			lastTime = currentTime;
		}

		// Poll input events
		Window::poll_events();

		while (lag >= world.time_step)
		{
			if (window.get_key(GLFW_KEY_ESCAPE))
			{
				shouldExit = true;
			}
			
			if (controller.get_jump())
			{
				world.push_event("jump");
			}
			if (controller.get_fire())
			{
				world.push_event("fire");
			}

			// Dispatch events
			world.push_event("move", controller.get_lstick());
			world.push_event("look", controller.get_rstick() / 15);
			window.center_cursor();

			// Update the world
			world.update();

			lag -= world.time_step;
			numUpdates++;
		}

		if (drawPhysicsKey.update(window))
		{
			drawPhysics = !drawPhysics;
		}

		// Render the frame
		if (drawPhysics)
		{
			physics.debug_draw(renderer);
		}

		renderer.render_world(world, 2);
		window.swap_buffers();
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

		// Create world
		Console::WriteLine("Loading world: '@'...", argv[2]);
		willow::World world;
		
		// Create physcs system
		willow::BulletPhysicsSystem physics;
		world.add_system(physics);

		// Create animation system
		willow::AnimationSystem animation;
		world.add_system(animation);

		// Deserialize it
		{
			willow::XMLArchive archive;
			archive.load(argv[2]);

			try
			{
				archive.deserialize(world);
			}
			catch (Exception& e)
			{
				Console::Error("Could not load scene, error during deserialization: @", e);
				Application::Terminate(EXIT_FAILURE);
			}
		}

		// Load up subsystems
		Console::WriteLine("Initializing subsystems...");
		Window window("Willow Engine", 1280, 720);
		willow::GLRenderSystem renderer(window.get_width(), window.get_height());
		world.add_system(renderer);

		// Enter main event loop
		Console::WriteLine("Entering event loop...");
		event_loop(window, world, renderer, physics);
	}
	
	Application::Terminate();
}
