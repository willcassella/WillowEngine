//Willow Engine Init code!
//By Will Cassella

// Show console in debug mode
#ifdef DEBUG
#define WinMain main
#endif

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>

//Include module files
#include <ScriptingModule.h>
#include <RenderModule.h>

//Define context parameters
int window_width = 1280;
int window_height = 720;
const char* title = "Willow Engine";
bool fullscreen = false;

//Function Prototypes
GLFWwindow* InitGLFW();
bool InitGlew();
void eventLoop( GLFWwindow* window );
void cleanUp( GLFWwindow* window );

void windowSizeCallback( GLFWwindow* window, int x, int y )
{
	//Resize the viewport
	glViewport(0, 0, x, y);
}

int main( int argc, char* argv[] )
{	
	std::cout << "Initializing subsystems... " << std::endl;
	//Initialize GLFW and get a window
	GLFWwindow* window = InitGLFW();
  
	// Make an openGL context in window
	glfwMakeContextCurrent(window);

	//Initialize GLEW and check for errors
	if ( !InitGlew() )
	{
		return -1;
	}

	//Initialize the scripting engine
	InitScriptingModule();

	//Initialize the renderer
	Renderer::init();


	
	///////////////////////////////
	///   Setting up a simple   ///
	///          scene          ///
	///////////////////////////////

	GameObject teapot;

	//Create a simple mesh to render
	Mesh teapot_mesh;
	teapot_mesh.Load( "teapot.obj" );
	
	Shader frag;
	Shader vert;

	frag.Load( Shader::basic_frag_source, GL_FRAGMENT_SHADER );
	vert.Load( Shader::basic_vert_source, GL_VERTEX_SHADER );

	Material mat;
	mat.Load( &vert, &frag );

	Texture tex ("teapot_tex.png");
	mat.texture = &tex;

	teapot_mesh.AssignMat( &mat );

	teapot.mesh = &teapot_mesh;

	Camera cam( 43, float(window_width)/window_height, 0.2f, 60.0f );

	cam.transform.position.z = 4;
	cam.transform.position.y = 1;



	//Execute the main event loops
	eventLoop( window );
	
	//Cleanup the engine
	cleanUp( window );

	return 0;
}

GLFWwindow* InitGLFW()
{
	//Initailize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	// Make the window invisible
	glfwWindowHint( GLFW_VISIBLE, GL_FALSE );

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
	glfwSetWindowPos( window, posx, posy );

	//Make the window visible
	glfwShowWindow( window );

	// Make the cursor invisible
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	// Move the cursor to the center of the screen
	glfwSetCursorPos( window, window_width/2, window_height/2 );

	//Set the window callbacks
	glfwSetWindowSizeCallback( window, windowSizeCallback );

	// Create the frambuffer and viewport
	glfwGetFramebufferSize(window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);

	return window;
}

bool InitGlew()
{
	//Initializw GLEW with experimental extensions
	glewExperimental = GL_TRUE;
	return glewInit() == GLEW_OK;
}

void eventLoop( GLFWwindow* window )
{
	std::cout << "Entering event loop... " << std:: endl;

	//Execute the main function
	std::cout << "	Executing scripts..." << std::endl;
	ExecuteMain();

	double lastTime = glfwGetTime();
	int nbFrames = 0;

     // Measure speed
     double currentTime = glfwGetTime();
     nbFrames++;

	//Begine the event loop
	while ( !glfwWindowShouldClose(window) )
	{
		 
		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(nbFrames));
         nbFrames = 0;
         lastTime += 1.0;
		};
		
		glfwPollEvents();

		//render the frame
		Renderer::render( window );
	}
	std::cout << "Leaving event loop... " << std::endl;
}

void cleanUp( GLFWwindow* window )
{
	std::cout << "Shutting down..." << std::endl;
	
	//Delete the window (along with the context)
	glfwDestroyWindow( window );
	
	//Quit GLFW
	glfwTerminate();
}