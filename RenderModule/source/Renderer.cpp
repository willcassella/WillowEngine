// Renderer.cpp

#include "Renderer.h"

#include <GLFW\glfw3.h>
#include <forward_list>

#include "Mesh.h"
#include "GameObject.h"
#include "Mat4.h"

RenderQueue Renderer::rqueue;
CameraQueue Renderer::cqueue;

int Renderer::init()
{
	// Set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	return 0;
}

int Renderer::render( GLFWwindow* window )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Create an iterator
	//std::forward_list< GameObject* >::iterator object;

	GameObject* object = rqueue.front();

	//Get the current camera
	Camera* cam = cqueue.front();

	// Call the camera's update function
	cam->Update( window );

	// Call the object's update function
	object->Update();

	//Iterate throught the render queue
    //for (object = rqueue.begin() ; object != rqueue.end(); object++){

		// Bind the mesh
		glBindVertexArray( object->mesh->vao );
		
		// Get the model matrix
		Mat4  model = object->transform.getModel();
		
		// Get the view matrix
		Mat4 view = cam->transform.getModel().inverse();

		// Create the clipspace matrix
		Mat4 clipspace = cam->perspective * view * model;

		// Upload the matrix to the GPU
		glUniformMatrix4fv( object->mesh->mat->clipspace, 1, GL_FALSE,  clipspace[0] );
		
		//Draw the mesh
		glDrawElements( GL_TRIANGLES, (GLsizei)object->mesh->elements.size(), GL_UNSIGNED_INT, 0 );
	//};
	
	glBindVertexArray( 0 );
	
	//update the screen
	glfwSwapBuffers( window );

	return 0;
}