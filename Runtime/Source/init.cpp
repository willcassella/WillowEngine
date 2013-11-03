//Willow Engine Init code!
//By Will Cassella
#define _HEADERS_INCLUDED_
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL.h>

//Include custom files
#include <ScriptingModule.h>
#include <RenderModule.h>

//Define context parameters
unsigned int window_width = 800;
unsigned int window_height = 600;
const char* title = "Willow Engine";

//Function Prototypes
SDL_Window* InitSDL( Uint32 flags );
bool InitGlew();
void eventLoop( SDL_Window* window );
void cleanUp( SDL_GLContext context );

int main( int argc, char* argv[] )
{	
	std::cout << "Initializing subsystems... " << std::endl;
	//Initialize SDL and get the window
	SDL_Window* window = InitSDL( SDL_INIT_VIDEO );
  
	// Create an OpenGL context associated with the window.
	SDL_GLContext glcontext = SDL_GL_CreateContext( window );

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

		int square_elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		//Create a simple mesh to render
		Mesh simple ( square_vertices, sizeof( square_vertices ), square_elements, sizeof( square_elements ) );

		Shader simple_vert ( Shader::basic_vert_source, GL_VERTEX_SHADER );
		Shader simple_frag ( Shader::basic_frag_source, GL_FRAGMENT_SHADER );

		Material simple_mat ( &simple_vert, &simple_frag );

		simple.mat = &simple_mat;

	//Execute the main event loops
	eventLoop( window );
	
	//Cleanup the engine
	cleanUp( glcontext );

	return 0;
}

SDL_Window* InitSDL( Uint32 flags )
{
	//Initailize SDL
	SDL_Init( flags );

	//Create the SDL window
	return SDL_CreateWindow( title,
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          window_width, window_height,
						  SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL );
}

bool InitGlew()
{
	//Initializw GLEW with experimental extensions
	glewExperimental = GL_TRUE;
	return glewInit() == GLEW_OK;
}

void eventLoop( SDL_Window* window )
{
	//Define the windowEvent
	SDL_Event windowEvent;

	std::cout << "Entering event loop... " << std:: endl;

	//Execute the main function
	std::cout << "	Executing scripts..." << std::endl;
	ExecuteMain();

	//Begine the event loop
	while ( true )
	{
		if ( SDL_PollEvent( &windowEvent ) )
		{
			if ( windowEvent.type == SDL_QUIT ) break; 
		}
		//render the frame
		Renderer::render( window );
	}
	std::cout << "Leaving event loop... " << std::endl;
}

void cleanUp( SDL_GLContext context )
{
	std::cout << "Shutting down..." << std::endl;
	
	//Delete the openGL rendering context
	SDL_GL_DeleteContext( context ); 
	
	//Quit SDl
	SDL_Quit();
}