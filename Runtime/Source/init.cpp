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

//Include modules files
#include <ScriptingModule.h>
#include <RenderModule.h>

//Define context parameters
int window_width = 800;
int window_height = 600;
const char* title = "Willow Engine";

//Function Prototypes
GLFWwindow* InitGLFW();
bool InitGlew();
void eventLoop( GLFWwindow* window );
void cleanUp( GLFWwindow* window );

void windowPosCallback( GLFWwindow* window, int x, int y )
{
	std::cout << "Position: " << x << ", " << y <<std::endl;
}
void windowSizeCallback( GLFWwindow* window, int x, int y )
{
	std::cout << "Size: " << x << ", " << y << std::endl;
}

int WinMain( int argc, char* argv[] )
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

	//instantiate objects

	float square_vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	float tri_vertices[] = {
		 0.8f, -0.7f, 1.0f, 0.0f, 1.0f, // Top
		 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // Bottom-right
		 0.6f, -1.0f, 1.0f, 1.0f, 0.0f  // Bottomr-left
	};

	GLuint square_elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint tri_elements[] = {
		0, 1, 2
	};

	//Create a simple mesh to render
	Mesh simple;
	simple.Load( square_vertices, sizeof( square_vertices ), square_elements, sizeof( square_elements ) );
	
	Shader frag ( Shader::basic_frag_source, GL_FRAGMENT_SHADER );
	Shader vert ( Shader::basic_vert_source, GL_VERTEX_SHADER );

	Material mat ( &vert, &frag );

	simple.AssignMat( &mat );
	
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

	//move the window to the center of the screen
	glfwSetWindowPos( window, 550, 250 );

	//Make the window visible
	glfwShowWindow( window );

	//Set the window callbacks
	glfwSetWindowPosCallback( window, windowPosCallback );
	glfwSetWindowSizeCallback( window, windowSizeCallback );

	// Create the frambuffer and viewport
	glfwGetFramebufferSize(window, &window_width, &window_width);
	glViewport(0, 0, window_width, window_width);

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

	//Begine the event loop
	while ( !glfwWindowShouldClose(window) )
	{
		//render the frame
		Renderer::render( window );

		glfwPollEvents();
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