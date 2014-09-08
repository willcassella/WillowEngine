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
//#include <Scripting\Scripting.h>
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
	//Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();
  
	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	//Initialize the scripting engine
	//InitScriptingModule();

	//Initialize the renderer
	Render::InitRenderer(Render::API::API_OPENGL);

	///////////////////////////////
	///   Setting up a simple   ///
	///          scene          ///

	Scene testScene;

	Prop sponza("sponza");
	Prop gun("gun");
	Prop crosshairs("crosshairs");

	//Create a simple mesh to render
	Render::StaticMesh sponza_mesh("sponza.dat");
	Render::StaticMesh gun_mesh("battle_rifle.dat");
	Render::StaticMesh crosshairs_mesh("battle_rifle_crosshairs.dat");

	Render::Shader frag(Render::Shader::basic_frag_source, Render::ShaderType::FRAGMENT_SHADER);
	Render::Shader vert(Render::Shader::basic_vert_source, Render::ShaderType::VERTEX_SHADER);

	Render::Material sponza_mat(vert, frag);
	Render::Material gun_mat(vert, frag);
	Render::Material crosshairs_mat(vert, frag);

	Render::Texture sponza_tex ("sponza_tex.png");
	sponza_mat.setTexture(sponza_tex);

	Render::Texture gun_tex("battle_rifle_tex.png");
	gun_mat.setTexture(gun_tex);

	Render::Texture crosshairs_tex("battle_rifle_crosshair_tex.png");
	crosshairs_mat.setTexture(crosshairs_tex);

	sponza_mesh.setMaterial(sponza_mat);
	gun_mesh.setMaterial(gun_mat);
	crosshairs_mesh.setMaterial(crosshairs_mat);

	sponza.mesh = &sponza_mesh;
	gun.mesh = &gun_mesh;
	crosshairs.mesh = &crosshairs_mesh;

	Camera cam("Camera", 43, float(window_width)/window_height, 0.01f, 90.0f);

	cam.transform.position.z = 4;
	cam.transform.position.y = 0;

	gun.transform.scale = Math::Vec3(0.2f, 0.2f, 0.2f);
	gun.transform.position.x = 0.08f;
	gun.transform.position.z = -0.17f;
	gun.transform.position.y = -0.14f;
	gun.transform.rotate(Math::Vec3::UP, -3.14159f/2, false);
	gun.transform.rotate(Math::Vec3::RIGHT, 3.14159f/25, false);
	gun.transform.parent = &cam.transform;

	crosshairs.transform.scale = Math::Vec3(0.13f, 0.13f, 0.13f);
	crosshairs.transform.position.z = -1;
	crosshairs.transform.position.y = -0.02f;
	crosshairs.transform.rotate(Math::Vec3::RIGHT, -3.14159f/2, false);
	crosshairs.transform.parent = &cam.transform;

	testScene.objects.add(&sponza);
	testScene.objects.add(&gun);
	testScene.objects.add(&crosshairs);
	testScene.cameras.add(&cam);




	//Execute the main event loops
	eventLoop(window, testScene);
	
	//Cleanup the engine
	cleanUp(window);

	return 0;
}

GLFWwindow* InitGLFW()
{
	//Initailize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	
	// Make the window invisible
	glfwWindowHint( GLFW_VISIBLE, false );

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );

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

	// Create the frambuffer and viewport
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

		if (currentTime - lastTime >= 1.0)
		{ 
			std::cout << 1000.0 / numFrames << " ms/frame" << std::endl;
			numFrames = 0;
			lastTime = currentTime;
		}

		// Update the scene
		scene.update((float)(currentTime - frameTime));
		frameTime = glfwGetTime();

		//render the frame
		Render::clearBuffer();
		scene.render();
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