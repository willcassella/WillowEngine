//Willow Engine Init code!
//By Will Cassella
#define _HEADERS_INCLUDED_
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL.h>

//Include custom files
//#include "Renderer.h"
#include <ScriptingModule.h>
#include <RenderModule.h>

//Define context parameters
unsigned int window_width = 800;
unsigned int window_height = 600;
const char* title = "Willow Engine";

//Create the renderer
Renderer rend;

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
	//rend.Init();
	Renderer::init();
	
	Mesh plane (Mesh::square);

	std::cout << "Compiling shaders... " << std::endl;
	//Create the vertex shaders
	Shader vertexShader ( "vert.glsl", GL_VERTEX_SHADER );
	Shader fragmentShader ( "frag.glsl", GL_FRAGMENT_SHADER );

	//Input the shaders
	//rend.program.addShader( vertexShader );
	//rend.program.addShader( fragmentShader );

	std::cout << "Linking the renderer... " << std::endl;
	//Link the renderer
	//rend.compile();

	//Check for OpenGL errors
	GLenum error = glGetError();
	if( error != 0 )
	{
		std::cout << "OpenGl AFTER error: " << error << std:: endl;
	}

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

	//Set the openGL clear color, and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	std::cout << "Entering event loop... " << std:: endl;

	//Execute the main function
	std::cout << "Executing scripts..." << std::endl;
	ExecuteMain();

	//Begine the event loop
	while ( true )
	{
		if ( SDL_PollEvent( &windowEvent ) )
		{
			if ( windowEvent.type == SDL_QUIT ) break; 
		}

		//render the frame
		//int err = rend.render( window );
		//if ( err != 0 )
		//{
			//printf( "Fatal error!" );

			//break;
		//}
	}

	std::cout << "Leaving event loop... " << std::endl;
}

void cleanUp( SDL_GLContext context )
{
	std::cout << "Shutting down..." << std::endl;
	//Delete the renderer
	rend.~Renderer();
	
	//Delete the openGL rendering context
	SDL_GL_DeleteContext( context ); 
	
	//Quit SDl
	SDL_Quit();
}