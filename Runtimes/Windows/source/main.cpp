// Willow Engine Init code!
// By Will Cassella

// Show console in debug mode
#ifdef DEBUG
#define WinMain main
#endif

#include <iostream>
#include <GLFW/glfw3.h>

//Include modules headers
#include <Core\Scene.h>
#include <Render\Render.h>

//Define context parameters
int window_width = 1280;
int window_height = 720;
const char* title = "Willow Engine";
bool fullscreen = true;

//Function Prototypes
GLFWwindow* InitGLFW();
void eventLoop(GLFWwindow* window, Willow::Scene& scene);
void cleanUp(GLFWwindow* window);

void windowSizeCallback(GLFWwindow* window, int x, int y)
{
	//Resize the viewport
	glViewport(0, 0, x, y);
}

int main(int argc, char* argv[])
{	
	using namespace Willow;

	std::cout << "Initializing subsystems... " << std::endl;
	// Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();
  
	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	// Initialize the renderer
	InitRenderer(API::OpenGL);

	///////////////////////////////
	///   Setting up a simple   ///
	///          scene          ///

	Scene testScene;

	Prop sponza("sponza");
	Prop gun("gun");
	Prop crosshairs("crosshairs");

	sponza.mesh = "data/sponza.dat";
	gun.mesh = "data/battle_rifle.dat";
	crosshairs.mesh = "data/battle_rifle_crosshairs.dat";

	Material sponza_mat;
	sponza_mat.VertexShader = "data/Default.vert";
	sponza_mat.FragmentShader = "data/Default.frag";
	sponza_mat.Textures["fDiffuse"] = "data/sponza_tex.png";
	sponza_mat.Compile();
	sponza.mesh->SetMaterial(sponza_mat);

	Material gun_mat;
	gun_mat.VertexShader = "data/Default.vert";
	gun_mat.FragmentShader = "data/Default.frag";
	gun_mat.Textures["fDiffuse"] = "data/battle_rifle_tex.png";
	gun_mat.Compile();
	gun.mesh->SetMaterial(gun_mat);

	Material crosshairs_mat;
	crosshairs_mat.VertexShader = "data/Default.vert";
	crosshairs_mat.FragmentShader = "data/Default.frag";
	crosshairs_mat.Textures["fDiffuse"] = "data/battle_rifle_crosshair_tex.png";
	crosshairs_mat.Compile();
	crosshairs.mesh->SetMaterial(crosshairs_mat);

	Camera cam("Camera", 43, float(window_width)/window_height, 0.01f, 90.0f);

	cam.Transform.Location.Z = 4;
	cam.Transform.Location.Y = 0;

	// @TODO: Parenting seems to be broken...
	//gun.Transform.Parent = &cam.Transform;

	crosshairs.Transform.Location.Z = -1;
	crosshairs.Transform.Location.Y = -0.02f;
	crosshairs.Transform.Rotate(Vec3::Right, -3.14159f/2, false);
	crosshairs.Transform.Parent = &cam.Transform;

	testScene.Objects.Add(&sponza);
	testScene.Objects.Add(&gun);
	testScene.Objects.Add(&crosshairs);
	testScene.Cameras.Add(&cam);


	//Execute the main event loops
	eventLoop(window, testScene);
	
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

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, 
		title, NULL, NULL);

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

void eventLoop(GLFWwindow* window, Willow::Scene& scene)
{
	std::cout << "Entering event loop... " << std::endl;

	double lastTime = glfwGetTime();
	double frameTime = lastTime;
	int numFrames = 0;

	//Begin the event loop
	while (!glfwWindowShouldClose(window))
	{	 
		// If we reported the frame time more than one second ago
		double currentTime = glfwGetTime();
		numFrames++;

		// @TODO: replace this with a config file or something
#if defined(DEBUG)
		if (currentTime - lastTime >= 1.0)
		{ 
			std::cout << 1000.0 / numFrames << " ms/frame" << std::endl;
			numFrames = 0;
			lastTime = currentTime;
		}
#endif

		// Poll input events
		glfwPollEvents();

		scene.DispatchEvent("Forward", 0.001f);

		// Update the scene
		scene.Update((float)(currentTime - frameTime));
		frameTime = glfwGetTime();

		//render the frame
		Willow::ClearBuffer();
		scene.Render();
		glfwSwapBuffers(window);
	}
	std::cout << "Leaving event loop... " << std::endl;
}

void cleanUp(GLFWwindow* window)
{
	std::cout << "Shutting down..." << std::endl;
	
	//Delete the window (along with the context)
	glfwDestroyWindow( window );
	
	//Quit GLFW
	glfwTerminate();
}