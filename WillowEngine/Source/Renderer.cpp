#include "Renderer.h"

float vertices[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right

     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, // Bottom-left
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f  // Top-left
};

Renderer::Renderer()
{
	//vertices = INIT_vertices;
	program.getId();
}


Renderer::~Renderer()
{
	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );
	program.~RenderProgram();
}


void Renderer::Init()
{
	//Set the openGL clear color, and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );
	
	//Initiate the render program
	program.init();

	//Set up Vertex Array Object
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	//Set up Vertex Buffer Object
	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	GLenum error = glGetError();
	if( error != 0 )
	{
		std::cout << "OpenGl INIT1 error: " << error << std:: endl;
	}
}


void Renderer::compile()
{
	program.compile();
	program.use();

	GLenum error = glGetError();
	if( error != 0 )
	{
		std::cout << "OpenGl INIT1 error: " << error << std:: endl;
	}

	if( error != 0 )
	{
		std::cout << "OpenGl INIT2 error: " << error << std:: endl;
	}

	if( error != 0 )
	{
		std::cout << "OpenGl INIT3 error: " << error << std:: endl;
	}
	
	//I NEED TO FIND A BETTER PLACE FOR THIS
	GLint posAttrib = glGetAttribLocation( program, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE,
                       5*sizeof(float), 0 );

	GLint colAttrib = glGetAttribLocation( program, "color" );
	glEnableVertexAttribArray( colAttrib );
	glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE,
                       5*sizeof(float), (void*)( 2*sizeof(float) ) );
}


int Renderer::render( SDL_Window* window )
{
	//Clear the screen
	glClear( GL_COLOR_BUFFER_BIT );

	//NEEDS FIXING
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	
	//Swap the buffer
	SDL_GL_SwapWindow( window );
	
	//Check for errors
	GLenum error = glGetError();
	if( error != 0 )
	{
		std::cout << "OpenGl RENDER error: " << error << std::endl;
	}

	return 0;
}