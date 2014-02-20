// Willow Engine Init code!
// By Will Cassella

// Show console in debug mode
#ifdef DEBUG
#define WinMain main
#endif

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Include subsytem files
#include <Engine.h>
#include <Render.h>
#include <Scripting.h>

//Define context parameters
int window_width = 1280;
int window_height = 720;
const char* title = "Willow Engine";
bool fullscreen = true;

//Function Prototypes
GLFWwindow* InitGLFW();
bool InitGlew();
void eventLoop( GLFWwindow* window, const Scene& scene );
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
	Renderer::init( RENDER_OPENGL );


	
	///////////////////////////////
	///   Setting up a simple   ///
	///          scene          ///
	///////////////////////////////

	Scene testScene;

	GameObject sponza( "sponza" );
	GameObject gun( "gun" );
	GameObject crosshairs( "crosshairs" );

	//Create a simple mesh to render
	StaticMesh sponza_mesh( "sponza.dat" );
	StaticMesh gun_mesh( "battle_rifle.dat" );
	StaticMesh crosshairs_mesh( "battle_rifle_crosshairs.dat" );

	Shader frag( Shader::basic_frag_source, GL_FRAGMENT_SHADER );
	Shader vert( Shader::basic_vert_source, GL_VERTEX_SHADER );

	std::string acid_shader =
	"#version 330 core\n"
    "in vec3 vPosition;"
	"in vec3 vNormal;"
    "in vec2 vTexcoord;"
	"out vec3 Position;"
	"out vec3 Normal;"
	"out vec2 Texcoord;"
	"uniform mat4 vModel;"
	"uniform mat4 vView;"
	"uniform mat4 vProjection;"
	"uniform float Time;"
    "void main() {"
	"	float offset = sin(Time+vPosition.y)/(5/vPosition.y);"
	"	vec4 acid_pos = vec4(vPosition.x, vPosition.y, vPosition.z+offset, 1);"
	"   gl_Position = vProjection * vView * vModel * acid_pos;"
	"	Texcoord = vec2( vTexcoord.x, 1.0 - vTexcoord.y );"
	"	Position = vPosition;"
	"	Normal = vNormal;"
    "}";

	Shader acid( acid_shader, GL_VERTEX_SHADER );


	Material sponza_mat( vert, frag );
	Material gun_mat( vert, frag );
	Material crosshairs_mat( vert, frag );

	Texture sponza_tex ("sponza_tex.png");
	sponza_mat.setTexture( sponza_tex );

	Texture gun_tex( "battle_rifle_tex.png" );
	gun_mat.setTexture( gun_tex );

	Texture crosshairs_tex( "battle_rifle_crosshair_tex.png" );
	crosshairs_mat.setTexture( crosshairs_tex );

	sponza_mesh.setMaterial( sponza_mat );
	gun_mesh.setMaterial( gun_mat );
	crosshairs_mesh.setMaterial( crosshairs_mat );

	sponza.mesh = &sponza_mesh;
	gun.mesh = &gun_mesh;
	crosshairs.mesh = &crosshairs_mesh;

	Camera cam( 43, float(window_width)/window_height, 0.01f, 90.0f );

	cam.transform.position.z = 4;
	cam.transform.position.y = 1;

	gun.transform.scale = Vec3( 0.2f, 0.2f, 0.2f );
	gun.transform.position.x = 0.08f;
	gun.transform.position.z = -0.17f;
	gun.transform.position.y = -0.14f;
	gun.transform.rotate( Vec3::UP, -3.14159f/2, false );
	gun.transform.rotate( Vec3::RIGHT, 3.14159f/25, false );
	gun.transform.parent = &cam.transform;

	crosshairs.transform.scale = Vec3( 0.13f, 0.13f, 0.13f );
	crosshairs.transform.position.z = -1;
	crosshairs.transform.position.y = -0.02f;
	crosshairs.transform.rotate( Vec3::RIGHT, -3.14159f/2, false );
	crosshairs.transform.parent = &cam.transform;

	testScene.objects.push_back( &sponza );
	testScene.objects.push_back( &gun );
	testScene.objects.push_back( &crosshairs );
	testScene.cameras.push_back( &cam );


	//Execute the main event loops
	eventLoop( window, testScene );
	
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

void eventLoop( GLFWwindow* window, const Scene& scene )
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

		// Update all game objects
		for( int i = 0; i < scene.objects.size(); i++ ) {
			scene.objects[i]->Update();
		}

		// Update all cameras
		for( int i = 0; i < scene.cameras.size(); i++ ) {
			scene.cameras[i]->Update( window );
		}

		//render the frame
		Renderer::render( scene );

		glfwSwapBuffers( window );
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