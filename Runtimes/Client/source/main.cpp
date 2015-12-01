// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <GLFW/glfw3.h>
#include <Core/Console.h>
#include <Core/Math/Vec2.h>
#include <GLRender/GLRenderer.h>
#include <Engine/GameObjects/Prop.h>
#include <ExampleGame/FPSCamera.h>

//Define context parameters
int32 window_width = 1280;
int32 window_height = 720;

//Function Prototypes
GLFWwindow* InitGLFW();
void eventLoop(GLFWwindow* window, Scene& scene, IRenderer& renderer);
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

	// Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();

	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	// Create the renderer and scene to simulate
	{
		GLRenderer renderer(window_width, window_height);

		///////////////////////////////
		///   Setting up a simple   ///
		///          scene          ///

		UniquePtr<Scene> scene = New<Scene>();

		auto& sponza = scene->Spawn<Prop>();
		sponza.GetTransform()->Scale3D(Vec3{ 0.6f, 0.6f, 0.6f });
		sponza.GetComponent(sponza.GetStaticMeshComponent())->Mesh = "Content/Models/sponza_new.wmesh"_p;
		sponza.GetComponent(sponza.GetStaticMeshComponent())->Material = "Content/Materials/Sponza.mat"_p;
		sponza.GetComponent(sponza.GetStaticMeshComponent())->InstanceParams["diffuse"] = AssetPtr<Texture>("Content/Textures/sponza_new_tex.png"_p);

		auto& cam = scene->Spawn<FPSCamera>();
		cam.GetTransform()->Location.Y += 3;

		//Execute the main event loop
		eventLoop(window, *scene, renderer);
	}

	//Cleanup the engine
	cleanUp(window);
	
	Application::Terminate();
}

GLFWwindow* InitGLFW()
{
	//Initialize GLFW
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

void eventLoop(GLFWwindow* window, Scene& scene, IRenderer& renderer)
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

		while (lag >= scene.TimeStep)
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
				scene.Events.DispatchEvent("Poof");
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			{
				exit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_Q))
			{
				scene.Events.DispatchEvent("Spin", 0.5f);
			}
			if (moveAccum != Vec2(0, 0))
			{
				scene.Events.DispatchEvent("Move", moveAccum.Normalize());
			}

			scene.Events.DispatchEvent("Look", Vec2(Cursor.Position.X / 100, Cursor.Position.Y / 100));
			Cursor.SetPosition(window, 0, 0);

			// Update the scene
			scene.Update();

			lag -= scene.TimeStep;
			numUpdates++;
		}

		//render the frame
		renderer.RenderScene(scene);
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
