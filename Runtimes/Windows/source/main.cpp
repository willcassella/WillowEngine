// Willow Engine Init code!
// By Will Cassella

// Show console in debug mode
#ifdef DEBUG
#define WinMain main
#endif

#include <GLFW/glfw3.h>
#include <Utility\Console.h>
#include <Utility\Math\Vec2.h>
#include <Core\Game.h>
#include <Render\Prop.h>
#include <ExampleGame\FPSCamera.h>
#include <ExampleGame\Ghost.h>
using namespace Willow;

//Define context parameters
int32 window_width = 1280;
int32 window_height = 720;

//Function Prototypes
GLFWwindow* InitGLFW();
void eventLoop(GLFWwindow* window);
void cleanUp(GLFWwindow* window);

struct
{
	//////////////////
	///   Fields   ///
public:

	Willow::Vec2 Position;

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

void windowSizeCallback(GLFWwindow* window, int32 x, int32 y)
{
	//Resize the viewport
	glViewport(0, 0, x, y);
}

int main(int32 argc, char* argv[])
{	
	Console::WriteLine("Initializing subsystems...");

	// Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();
  
	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	// Initialize the renderer
	InitRenderer(window_width, window_height);

	///////////////////////////////
	///   Setting up a simple   ///
	///          scene          ///

	Scene& test = Game::Instance().GetCurrentScene();

	auto& sponza = test.AddObject<Prop>("sponza");
	sponza.MeshComponent.Mesh = "data/sponza.dat";
	sponza.MeshComponent.Mesh->SetMaterial(String("data/Sponza.mat"));

	auto& gun = test.AddObject<ExampleGame::Ghost>("gun");
	gun.MeshComponent.Mesh = "data/battle_rifle.dat";
	gun.MeshComponent.Mesh->SetMaterial(String("data/Gun.mat"));

	auto& cam = test.AddObject<ExampleGame::FPSCamera>("Camera");
	test.Cameras.Add(&cam);

	Console::WriteLine(cam.GetComponents().GetType() == TypeInfo<List<Component*>>());

	//Execute the main event loop
	eventLoop(window);
	
	//Cleanup the engine
	cleanUp(window);

	return 0;
}

GLFWwindow* InitGLFW()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	
	// Make the window invisible
	glfwWindowHint(GLFW_VISIBLE, false);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Willow Engine", NULL, NULL);

	//make sure the window was initialized properly
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
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

	//Set the window callbacks
	glfwSetWindowSizeCallback(window, windowSizeCallback);

	// Create the frame buffer and viewport
	glfwGetFramebufferSize(window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);

	return window;
}

void eventLoop(GLFWwindow* window)
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
		Scene& scene = Game::Instance().GetCurrentScene();

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
			// Dispatch events
			float speed = 0.05f;
			if (glfwGetKey(window, GLFW_KEY_W))
			{
				scene.DispatchEvent("MoveForward", speed);
			}
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				scene.DispatchEvent("MoveForward", -speed);
			}
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				scene.DispatchEvent("MoveRight", speed);
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				scene.DispatchEvent("MoveRight", -speed);
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE))
			{
				scene.DispatchEvent("Poof", 0);
			}
			if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			{
				exit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_Q))
			{
				scene.DispatchEvent("Spin", speed);
			}

			scene.DispatchEvent("LookUp", Cursor.Position.Y / 100);
			scene.DispatchEvent("LookRight", Cursor.Position.X / 100);
			Cursor.SetPosition(window, 0, 0);

			// Update the scene
			scene.Update();

			lag -= scene.TimeStep;
			numUpdates++;
		}

		//render the frame
		BeginFrame();
		scene.Render();
		glfwSwapBuffers(window);
	}

	Console::WriteLine("Leaving event loop...");
}

void cleanUp(GLFWwindow* window)
{
	Console::WriteLine("Shutting down...");
	
	//Delete the window (along with the context)
	glfwDestroyWindow( window );
	
	//Quit GLFW
	glfwTerminate();
}