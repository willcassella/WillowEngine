// Renderer.cpp

#include "Renderer.h"
#include "Mesh.h"
#include <forward_list>
#include <GLFW\glfw3.h>
#include "GameObject.h"

#include <glm\gtc\type_ptr.hpp>

RenderQueue Renderer::rqueue;
CameraQueue Renderer::cqueue;

int Renderer::init()
{
	// Set the opengl clear color to black and clear the screen
	glClearColor( 0, 0, 0, 1 );
	glEnable( GL_DEPTH_TEST );
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

	//Iterate throught the render queue
    //for (object = rqueue.begin() ; object != rqueue.end(); object++){

		// Bind the mesh
		glBindVertexArray( object->mesh->vao );

		// Create the clipspace matrix
		glm::mat4 model;
		glm::mat4 view = glm::lookAt( 
			cam->transform.local,
			glm::vec3( 0, 0, 0 ), 
			glm::vec3(0.0f, 0.0f, 1.0f) );
		glm::mat4 clipspace = cam->perspective * view * model;

		// Upload the matrix to the GPU
		glUniformMatrix4fv( object->mesh->mat->clipspace, 1, GL_FALSE, glm::value_ptr( clipspace ) );
		
		//Draw the mesh
		glDrawElements( GL_TRIANGLES, (GLsizei)object->mesh->elements.size(), GL_UNSIGNED_INT, 0 );
	//};
	
	glBindVertexArray( 0 );
	
	//update the screen
	glfwSwapBuffers( window );

	return 0;
}