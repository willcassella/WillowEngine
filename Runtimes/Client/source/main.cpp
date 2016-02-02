// main.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <GLFW/glfw3.h>
#include <Core/IO/Console.h>
#include <Core/Math/Vec2.h>
#include <GLRender/GLRenderer.h>
#include <ExampleGame/FPSCharacter.h>
#include <Resource/Archives/XMLArchive.h>

//Define context parameters
int32 window_width = 1280;
int32 window_height = 720;

//Function Prototypes
GLFWwindow* InitGLFW();
void eventLoop(GLFWwindow* window, World& world, IRenderer& renderer);
void cleanUp(GLFWwindow* window);

struct
{
	//////////////////
	///   Fields   ///
public:

	Vec2 Position;

	///////////////////
	///   Methods   ///
public:

	void UpdatePosition(GLFWwindow* window)
	{
		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);

		Position.X = (float)x - window_width / 2;
		Position.Y = (float)y - window_height / 2;
	}
	void SetPosition(GLFWwindow* window, float x, float y)
	{
		glfwSetCursorPos(window, x + window_width / 2, y + window_height / 2);
		Position.X = x;
		Position.X = y;
	}

} Cursor;

int main(int32 /*argc*/, char** /*argv*/)
{
	Application::Initialize();

	Console::WriteLine("Initializing subsystems...");

	// TEST OUT SERIALIZATION

	Table<GameObject::ID, Vec4> nameTable;
	nameTable[1] = Vec4(1, 2, 3, 4);
	nameTable[2] = Vec4(6, 9, 2, 5);
	nameTable[3] = Vec4(1, 2, 3, 4);

	auto time = glfwGetTime();
	XMLArchive archive;
	archive.Serialize(nameTable);
	archive.Save("table.xml");
	//archive.Load("table.xml");
	//archive.Deserialize(nameTable);
	auto end = glfwGetTime();

	Console::WriteLine("Serialized table in @ milliseconds", end - time);

	// Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();

	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	// Create the renderer and world to simulate
	{
		GLRenderer renderer(window_width, window_height);

		///////////////////////////////
		///   Setting up a simple   ///
		///          scene          ///

		UniquePtr<World> world = New<World>();

		auto& sponza = world->Spawn<StaticMeshComponent>("Sponza");
		sponza.SetScale({ 0.6f, 0.6f, 0.6f });
		sponza.Mesh = "Content/Models/sponza_new.wmesh"_p;
		sponza.Material = "Content/Materials/Sponza.mat"_p;
		sponza.InstanceParams["diffuse"] = AssetPtr<Texture>("Content/Textures/sponza_new_tex.png"_p);

		auto& player = world->Spawn<FPSCharacter>("Player");
		player.Translate({ 0, 3, 0 });

		//Execute the main event loop
		eventLoop(window, *world, renderer);
	}

	//Cleanup the engine
	cleanUp(window);
	
	Application::Terminate();
}

GLFWwindow* InitGLFW()
{
	//Spawn GLFW
	if (!glfwInit())
	{
		Console::WriteLine("GLFW Initialization failure");
		Application::Terminate(EXIT_FAILURE);
	}

	// Make the window invisible
	glfwWindowHint(GLFW_VISIBLE, false);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Willow Engine", NULL, NULL);

	//make sure the window was initialized properly
	if (!window)
	{
		Console::WriteLine("Window failed to initialize properly");
		glfwTerminate();
		Application::Terminate(EXIT_FAILURE);
	}

	// figure out the center of the screen
	int screen_height = 1080;
	int screen_width = 1920;

	int posx = (screen_width - window_width)/2;
	int posy = (screen_height - window_height)/2;

	//move the window to the center of the screen
	glfwSetWindowPos(window, posx, posy);

	//Make the window visible
	glfwShowWindow(window);

	// Make the cursor invisible
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	// Move the cursor to the center of the screen
	glfwSetCursorPos(window, window_width/2, window_height/2);

	return window;
}

void eventLoop(GLFWwindow* window, World& world, IRenderer& renderer)
{
	Console::WriteLine("Entering event loop...");

	double previous = glfwGetTime();
	double lastTime = previous;
	double lag = 0.0;
	uint32 numFrames = 0;
	uint32 numUpdates = 0;
	bool exit = false;

	// Begin the event loop
	while (!glfwWindowShouldClose(window) && !exit)
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
		glfwPollEvents();

		Cursor.UpdatePosition(window);

		while (lag >= world.TimeStep)
		{
			Vec2 moveAccum;

			// Dispatch events
			if (glfwGetKey(window, GLFW_KEY_W))
			{
				moveAccum.Y += 1;
			}
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				moveAccum.Y -= 1;
			}
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				moveAccum.X += 1;
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				moveAccum.X -= 1;
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE))
			{
				world.Events.DispatchEvent("Poof");
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			{
				exit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_Q))
			{
				world.Events.DispatchEvent("Spin", 0.5f);
			}
			if (moveAccum != Vec2(0, 0))
			{
				world.Events.DispatchEvent("Move", moveAccum.Normalize());
			}

			world.Events.DispatchEvent("Look", Vec2(Cursor.Position.X / 100, Cursor.Position.Y / 100));
			Cursor.SetPosition(window, 0, 0);

			// Update the world
			world.Update();

			lag -= world.TimeStep;
			numUpdates++;
		}

		//render the frame
		renderer.RenderWorld(world);
		glfwSwapBuffers(window);

		// Free memory
		Application::GetMemoryManager().Sweep();
	}

	Console::WriteLine("Leaving event loop...");
}

void cleanUp(GLFWwindow* window)
{
	Console::WriteLine("Shutting down...");

	//Delete the window (along with the context)
	glfwDestroyWindow(window);

	//Quit GLFW
	glfwTerminate();
}
